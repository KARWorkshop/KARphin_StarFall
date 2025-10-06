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
  clientInstance.Connect(SteamNetworkingSockets(), netInfo);

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

  // Wait for read thread to exit.
  if (readThread.joinable())
    readThread.join();

  clientInstance.Shutdown();
  GameNetworkingSockets_Kill();
}

bool CEXIETHERNET::TAPNetworkInterface::IsActivated()
{
  return (clientInstance.steamNetworkingInterface != nullptr);
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
}

bool CEXIETHERNET::TAPNetworkInterface::SendFrame(const u8* frame, u32 size)
{
  INFO_LOG_FMT(SP1, "SendFrame {} bytes:\n{}", size, ArrayToString(frame, size, 0x10));

  // Copy to write buffer.
  mWriteBuffer.assign(frame, frame + size);
  mWritePending = true;

  //  Anything else, just send it to the server and let them parse it
  clientInstance.steamNetworkingInterface->SendMessageToConnection(
      clientInstance.m_hConnection, mWriteBuffer.data(), size,
                                        k_nSteamNetworkingSend_Reliable, nullptr);

  mWritePending = false;

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
