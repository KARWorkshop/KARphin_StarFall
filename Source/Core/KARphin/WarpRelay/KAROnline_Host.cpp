#include <KARphin/WarpRelay/KAROnline_Host.hpp>

 // starts hosting a instance
bool KAR::Online::Netplay::HostServerInstance::Host(ISteamNetworkingSockets* steamNetworkingInterface, const NetInfo& self)
{
  // Start listening
  SteamNetworkingIPAddr serverLocalAddr = self.IP_Port;
  SteamNetworkingConfigValue_t opt;
  opt.SetPtr(k_ESteamNetworkingConfig_Callback_ConnectionStatusChanged, nullptr);
  //(void*)SteamNetConnectionStatusChangedCallback);
  listenSocket = steamNetworkingInterface->CreateListenSocketIP(serverLocalAddr, 1, &opt);
  if (listenSocket == k_HSteamListenSocket_Invalid)
    ERROR_LOG_FMT(SP1, "Failed to listen on port {}", self.IP_Port.m_port);
  pollGroup = steamNetworkingInterface->CreatePollGroup();
  if (pollGroup == k_HSteamNetPollGroup_Invalid)
    ERROR_LOG_FMT(SP1, "Failed to listen on port {}", self.IP_Port.m_port);

  INFO_LOG_FMT(SP1, "Server listening on port {}\n", self.IP_Port.m_port);

  isRunning = true;

  return true;
}

// shutsdown the connection
void KAR::Online::Netplay::HostServerInstance::Shutdown(
    ISteamNetworkingSockets* steamNetworkingInterface)
{
  if (!isRunning)
    return;

  INFO_LOG_FMT(SP1, "Server Shutdown");

  steamNetworkingInterface->CloseListenSocket(listenSocket);
  listenSocket = k_HSteamListenSocket_Invalid;

  steamNetworkingInterface->DestroyPollGroup(pollGroup);
  pollGroup = k_HSteamNetPollGroup_Invalid;

  isRunning = false;
}
