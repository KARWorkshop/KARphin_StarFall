#include <KARphin/WarpRelay/KAROnline_Client.hpp>

//global static ptr of the client
static KAR::Online::Netplay::ClientInstance* instance = nullptr;

//when the connection status changes for the client || CALLBACK FUNC
static void CallbackFunc_ClientConnectionStateChange(SteamNetConnectionStatusChangedCallback_t* pInfo)
{
  instance->OnSteamNetConnectionStatusChanged(pInfo);
}

//the actual function for when the connection state changes
void KAR::Online::Netplay::ClientInstance::OnSteamNetConnectionStatusChanged(
    SteamNetConnectionStatusChangedCallback_t* pInfo)
{
  assert(pInfo->m_hConn == m_hConnection || m_hConnection == k_HSteamNetConnection_Invalid);

  // What's the state of the connection?
  switch (pInfo->m_info.m_eState)
  {
  case k_ESteamNetworkingConnectionState_None:
    // NOTE: We will get callbacks here when we destroy connections.  You can ignore these.
    break;

  case k_ESteamNetworkingConnectionState_ClosedByPeer:
  case k_ESteamNetworkingConnectionState_ProblemDetectedLocally:
  {
    shouldDisconnect = true;

    // Print an appropriate message
    if (pInfo->m_eOldState == k_ESteamNetworkingConnectionState_Connecting)
    {
      // Note: we could distinguish between a timeout, a rejected connection,
      // or some other transport problem.
      INFO_LOG_FMT(SP1, "We sought the remote host, yet our efforts were met with defeat.  {}",
             pInfo->m_info.m_szEndDebug);
    }
    else if (pInfo->m_info.m_eState == k_ESteamNetworkingConnectionState_ProblemDetectedLocally)
    {
      INFO_LOG_FMT(SP1, "Alas, troubles beset us; we have lost contact with the host.  {}",
             pInfo->m_info.m_szEndDebug);
    }
    else
    {
      // NOTE: We could check the reason code for a normal disconnection
      INFO_LOG_FMT(SP1, "The host hath bidden us farewell.  {}", pInfo->m_info.m_szEndDebug);
    }

    // Clean up the connection.  This is important!
    // The connection is "closed" in the network sense, but
    // it has not been destroyed.  We must close it on our end, too
    // to finish up.  The reason information do not matter in this case,
    // and we cannot linger because it's already closed on the other end,
    // so we just pass 0's.
    steamNetworkingInterface->CloseConnection(pInfo->m_hConn, 0, nullptr, false);
    m_hConnection = k_HSteamNetConnection_Invalid;
    break;
  }

  case k_ESteamNetworkingConnectionState_Connecting:
    // We will get this callback when we start connecting.
    // We can ignore this.
    break;

  case k_ESteamNetworkingConnectionState_Connected:
    INFO_LOG_FMT(SP1, "Connected to server OK");
    break;

  default:
    // Silences -Wswitch
    break;
  }
}

// connects to a host
bool KAR::Online::Netplay::ClientInstance::Connect(ISteamNetworkingSockets* _steamNetworkingInterface, const NetInfo& target)
{
  instance = this;
  steamNetworkingInterface = _steamNetworkingInterface;

  // Start connecting
  INFO_LOG_FMT(SP1, "Attempting to connect to {}\n", target.debugIPStr);
  SteamNetworkingConfigValue_t opt;
  opt.SetPtr(k_ESteamNetworkingConfig_Callback_ConnectionStatusChanged,
             (void*)CallbackFunc_ClientConnectionStateChange);
  m_hConnection = steamNetworkingInterface->ConnectByIPAddress(target.IP_Port, 1, &opt);
  if (m_hConnection == k_HSteamNetConnection_Invalid)
  {
    ERROR_LOG_FMT(SP1, "Failed to create connection");
    return false;
  }

  isRunning = true;

  return true;
}

// shutsdown the connection
void KAR::Online::Netplay::ClientInstance::Shutdown()
{
  if (!isRunning)
    return;

  steamNetworkingInterface->CloseConnection(m_hConnection, 0, "Disconnect from Match", false);

  INFO_LOG_FMT(SP1, "Client connection shutdown");

  isRunning = false;
}
