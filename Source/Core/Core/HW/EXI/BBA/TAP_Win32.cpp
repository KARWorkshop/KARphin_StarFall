// Copyright 2008 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include "Core/HW/EXI/BBA/TAP_Win32.h"
#include "Core/HW/EXI/EXI_DeviceEthernet.h"

#include "Common/Assert.h"
#include "Common/Logging/Log.h"
#include "Common/MsgHandler.h"
#include "Common/StringUtil.h"
#include "Core/HW/EXI/EXI_Device.h"

namespace ExpansionInterface
{
bool CEXIETHERNET::TAPNetworkInterface::Activate()
{
  if (IsActivated())
    return true;

  //inits game sockets
  KAR::Online::NetInfo netInfo = KAR::Online::NetInfo::GenerateDefault();
  if (!std::filesystem::exists(KAR::Online::NetInfo::GetFilepath()))
  {
    netInfo.SaveToDisc();
  }
  else
    netInfo.LoadFromDisc();

  // inits the netcode shit
  SteamDatagramErrMsg errMsg;
  if (!GameNetworkingSockets_Init(nullptr, errMsg))
  {
  }
  // FatalError("GameNetworkingSockets_Init failed.  %s", errMsg);
 /* if (netInfo.isHost)
  {
    serverHostInstance.Host(SteamNetworkingSockets(), netInfo);
    g_is_first_user = true;
  }*/
  clientInstance.Connect(SteamNetworkingSockets(), netInfo);

  ////TAP init
  //DWORD len;
  //std::vector<std::basic_string<TCHAR>> device_guids;

  //if (!Win32TAPHelper::GetGUIDs(device_guids))
  //{
  //  ERROR_LOG_FMT(SP1, "Failed to find a TAP GUID");
  //  return false;
  //}

  //for (const auto& device_guid : device_guids)
  //{
  //  if (Win32TAPHelper::OpenTAP(mHAdapter, device_guid))
  //  {
  //    INFO_LOG_FMT(SP1, "OPENED {}", WStringToUTF8(device_guid));
  //    break;
  //  }
  //}
  //if (mHAdapter == INVALID_HANDLE_VALUE)
  //{
  //  PanicAlertFmt("Failed to open any TAP");
  //  return false;
  //}

  ///* get driver version info */
  //ULONG info[3]{};
  //if (DeviceIoControl(mHAdapter, TAP_IOCTL_GET_VERSION, &info, sizeof(info), &info, sizeof(info),
  //                    &len, nullptr))
  //{
  //  INFO_LOG_FMT(SP1, "TAP-Win32 Driver Version {}.{} {}", info[0], info[1],
  //               info[2] ? "(DEBUG)" : "");
  //}
  //if (!(info[0] > TAP_WIN32_MIN_MAJOR ||
  //      (info[0] == TAP_WIN32_MIN_MAJOR && info[1] >= TAP_WIN32_MIN_MINOR)))
  //{
  //  PanicAlertFmtT("ERROR: This version of Dolphin requires a TAP-Win32 driver"
  //                 " that is at least version {0}.{1} -- If you recently upgraded your Dolphin"
  //                 " distribution, a reboot is probably required at this point to get"
  //                 " Windows to see the new driver.",
  //                 TAP_WIN32_MIN_MAJOR, TAP_WIN32_MIN_MINOR);
  //  return false;
  //}

  ///* set driver media status to 'connected' */
  //ULONG status = TRUE;
  //if (!DeviceIoControl(mHAdapter, TAP_IOCTL_SET_MEDIA_STATUS, &status, sizeof(status), &status,
  //                     sizeof(status), &len, nullptr))
  //{
  //  ERROR_LOG_FMT(SP1, "WARNING: The TAP-Win32 driver rejected a"
  //                     "TAP_IOCTL_SET_MEDIA_STATUS DeviceIoControl call.");
  //  return false;
  //}

  ///* initialize read/write events */
  //mReadOverlapped.hEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);
  //mWriteOverlapped.hEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);
  //if (mReadOverlapped.hEvent == nullptr || mWriteOverlapped.hEvent == nullptr)
  //  return false;

  mWriteBuffer.reserve(1518);


  return RecvInit();
}

void CEXIETHERNET::TAPNetworkInterface::Deactivate()
{
  if (!IsActivated())
    return;

  // Signal read thread to exit.
  readEnabled.Clear();
  readThreadShutdown.Set();

  // Cancel any outstanding requests from both this thread (writes), and the read thread.
  CancelIoEx(mHAdapter, nullptr);

  // Wait for read thread to exit.
  if (readThread.joinable())
    readThread.join();

  // Clean-up handles
  CloseHandle(mReadOverlapped.hEvent);
  CloseHandle(mWriteOverlapped.hEvent);
  CloseHandle(mHAdapter);
  mHAdapter = INVALID_HANDLE_VALUE;
  memset(&mReadOverlapped, 0, sizeof(mReadOverlapped));
  memset(&mWriteOverlapped, 0, sizeof(mWriteOverlapped));

  clientInstance.Shutdown();
  GameNetworkingSockets_Kill();
}

bool CEXIETHERNET::TAPNetworkInterface::IsActivated()
{
  return mHAdapter != INVALID_HANDLE_VALUE;
}

void CEXIETHERNET::TAPNetworkInterface::ReadThreadHandler(TAPNetworkInterface* self)
{
  while (!self->readThreadShutdown.IsSet())
  {
    DWORD transferred;

    // polls the messages
    ISteamNetworkingMessage* pIncomingMsg[99];
    int numMsgs = self->clientInstance.steamNetworkingInterface->ReceiveMessagesOnConnection(
        self->clientInstance.m_hConnection, pIncomingMsg, 99);
    uint16_t messageIndex = 0;
    while (numMsgs > 0 && messageIndex < numMsgs)
    {
      //(const u8*)pIncomingMsg->m_pData,
      //    pIncomingMsg->m_cbSize

      memcpy(self->m_eth_ref->mRecvBuffer.get(), pIncomingMsg[messageIndex]->GetData(),
             pIncomingMsg[messageIndex]->GetSize());
      transferred = pIncomingMsg[messageIndex]->GetSize();

      // Copy to BBA buffer, and fire interrupt if enabled.
      DEBUG_LOG_FMT(SP1, "Received {} bytes:\n {}", transferred,
                    ArrayToString(self->m_eth_ref->mRecvBuffer.get(), transferred, 0x10));
      if (self->readEnabled.IsSet())
      {
        self->m_eth_ref->mRecvBufferLength = transferred;
        self->m_eth_ref->RecvHandlePacket();
      }

      pIncomingMsg[messageIndex]->Release();
      messageIndex++;
    }
  }

    //// if (numMsgs == 0)
    //// return;
    //if (numMsgs < 0)
    //{
    //  // FatalError("Error checking for messages");
    //  InjectPacket((const u8*)pIncomingMsg->m_pData, pIncomingMsg->m_cbSize);

    //  // We don't need this anymore.
    //  pIncomingMsg->Release();
    //}

    //// Read from TAP into internal buffer.
    //if (ReadFile(self->mHAdapter, self->m_eth_ref->mRecvBuffer.get(), BBA_RECV_SIZE, &transferred,
    //             &self->mReadOverlapped))
    //{
    //  // Returning immediately is not likely to happen, but if so, reset the event state manually.
    //  ResetEvent(self->mReadOverlapped.hEvent);
    //}
    //else
    //{
    //  // IO should be pending.
    //  if (GetLastError() != ERROR_IO_PENDING)
    //  {
    //    ERROR_LOG_FMT(SP1, "ReadFile failed (err={:#x})", GetLastError());
    //    continue;
    //  }

    //  // Block until the read completes.
    //  if (!GetOverlappedResult(self->mHAdapter, &self->mReadOverlapped, &transferred, TRUE))
    //  {
    //    // If CancelIO was called, we should exit (the flag will be set).
    //    if (GetLastError() == ERROR_OPERATION_ABORTED)
    //      continue;

    //    // Something else went wrong.
    //    ERROR_LOG_FMT(SP1, "GetOverlappedResult failed (err={:#x})", GetLastError());
    //    continue;
    //  }
    //}

    //// Copy to BBA buffer, and fire interrupt if enabled.
    //DEBUG_LOG_FMT(SP1, "Received {} bytes:\n {}", transferred,
    //              ArrayToString(self->m_eth_ref->mRecvBuffer.get(), transferred, 0x10));
    //if (self->readEnabled.IsSet())
    //{
    //  self->m_eth_ref->mRecvBufferLength = transferred;
    //  self->m_eth_ref->RecvHandlePacket();
   // }
 // }
}

bool CEXIETHERNET::TAPNetworkInterface::SendFrame(const u8* frame, u32 size)
{
  INFO_LOG_FMT(SP1, "SendFrame {} bytes:\n{}", size, ArrayToString(frame, size, 0x10));

  // Check for a background write. We can't issue another one until this one has completed.
  //DWORD transferred;
  if (mWritePending)
  {
    // Wait for previous write to complete.
  //  if (!GetOverlappedResult(mHAdapter, &mWriteOverlapped, &transferred, TRUE))
  //    ERROR_LOG_FMT(SP1, "GetOverlappedResult failed (err={:#x})", GetLastError());
  }

  // Copy to write buffer.
  mWriteBuffer.assign(frame, frame + size);
  //mWritePending = true;

  //// Queue async write.
  //if (WriteFile(mHAdapter, mWriteBuffer.data(), size, &transferred, &mWriteOverlapped))
  //{
  //  // Returning immediately is not likely to happen, but if so, reset the event state manually.
  //  ResetEvent(mWriteOverlapped.hEvent);
  //}
  //else
  //{
  //  // IO should be pending.
  //  if (GetLastError() != ERROR_IO_PENDING)
  //  {
  //    ERROR_LOG_FMT(SP1, "WriteFile failed (err={:#x})", GetLastError());
  //    ResetEvent(mWriteOverlapped.hEvent);
  //    mWritePending = false;
  //    return false;
  //  }
  //}
  //  Anything else, just send it to the server and let them parse it
  clientInstance.steamNetworkingInterface->SendMessageToConnection(
      clientInstance.m_hConnection, mWriteBuffer.data(), size,
                                        k_nSteamNetworkingSend_Reliable, nullptr);

  //mWritePending = false;

  // Always report the packet as being sent successfully, even though it might be a lie
  m_eth_ref->SendComplete();
  return true;
}

bool CEXIETHERNET::TAPNetworkInterface::RecvInit()
{
  readThread = std::thread(ReadThreadHandler, this);
  return true;
}

void CEXIETHERNET::TAPNetworkInterface::RecvStart()
{
  readEnabled.Set();
}

void CEXIETHERNET::TAPNetworkInterface::RecvStop()
{
  readEnabled.Clear();
}
}  // namespace ExpansionInterface
