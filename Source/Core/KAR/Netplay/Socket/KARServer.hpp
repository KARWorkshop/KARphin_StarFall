#pragma once

//defines a server for KAR Matches

#include <SFML/Network/Packet.hpp>
#include <map>
#include <mutex>
#include <queue>
#include <sstream>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include "Common/Timer.h"
#include "Common/TraversalClient.h"
#include "Core/NetPlayProto.h"

#ifdef _WIN32
#include <Qos2.h>
#endif

#include <KAR/Netplay/NetworkBackend.hpp>

namespace KAR::Networking::Core
{
  class NetPlayServer : public Common::TraversalClientClient
  {
    //controller mappings
    NetPlay::PadMappingArray m_pad_map;
    NetPlay::PadMappingArray m_wiimote_map;

    //traversal client and server instance
    ENetHost* m_server = nullptr;
    Common::TraversalClient* m_traversal_client = nullptr;

    bool is_connected = false;

    bool m_is_running = false;
    bool m_do_loop = false;
    std::thread m_thread;
    Common::Timer m_ping_timer;
    u32 m_ping_key = 0;
    bool m_update_pings = false;
    u32 m_current_game = 0;
    unsigned int m_minimum_buffer_size = 0;

    //thread func for commands
    void ThreadFunc();

    //initalizes the server
    void Init(const KAR::Networking::Util::NetworkConnectionType connectMode);

    //shutsdown the server
    void Shutdown();

    void SendAsyncToClients(std::unique_ptr<sf::Packet> packet);

    bool ChangeGame(const std::string& game);
    bool ComputeMD5(const std::string& file_identifier);
    bool AbortMD5();
    void SendChatMessage(const std::string& msg);

    void SetNetSettings(const NetPlay::NetSettings& settings);

    bool StartGame();

    NetPlay::PadMappingArray GetPadMapping() const;
    void SetPadMapping(const NetPlay::PadMappingArray& mappings);

    NetPlay::PadMappingArray GetWiimoteMapping() const;
    void SetWiimoteMapping(const NetPlay::PadMappingArray& mappings);

    void AdjustMinimumPadBufferSize(unsigned int size);

    void KickPlayer(NetPlay::PlayerId player);

    u16 GetPort();

    std::unordered_set<std::string> GetInterfaceSet();
    std::string GetInterfaceHost(const std::string& inter);

#ifdef USE_UPNP
    void TryPortmapping(u16 port);
#endif

  private:
    class Client
    {
    public:
      NetPlay::PlayerId pid;
      std::string name;
      std::string revision;
      Common::TraversalClient::State game_status;

      ENetPeer* socket;
      u32 ping;
      float frame_time = 0;
      u32 current_game;

      unsigned int buffer = 0;

#ifdef _WIN32
      HANDLE qos_handle;
      QOS_FLOWID qos_flow_id;
#endif

      bool operator==(const Client& other) const { return this == &other; }
    };

    void SendToClients(sf::Packet& packet, const NetPlay::PlayerId skip_pid = 0);
    void Send(ENetPeer* socket, sf::Packet& packet);
    unsigned int OnConnect(ENetPeer* socket);
    unsigned int OnDisconnect(Client& player);
    unsigned int OnData(sf::Packet& packet, Client& player);

    void UpdatePadMapping();
    void UpdateWiimoteMapping();
    std::vector<std::pair<std::string, std::string>> GetInterfaceListInternal();

    NetPlay::NetSettings m_settings;

    std::map<NetPlay::PlayerId, Client> m_players;

    std::unordered_map<u32, std::vector<std::pair<NetPlay::PlayerId, u64>>> m_timebase_by_frame;
    bool m_desync_detected;

    struct
    {
      std::recursive_mutex game;
      // lock order
      std::recursive_mutex players;
      std::recursive_mutex async_queue_write;
    } m_crit;

    std::string m_selected_game;
    Common::SPSCQueue<std::unique_ptr<sf::Packet>, false> m_async_queue;

#ifdef USE_UPNP
    static void mapPortThread(const u16 port);
    static void unmapPortThread();

    static bool initUPnP();
    static bool UPnPMapPort(const std::string& addr, const u16 port);
    static bool UPnPUnmapPort(const u16 port);

    static struct UPNPUrls m_upnp_urls;
    static struct IGDdatas m_upnp_data;
    static std::string m_upnp_ourip;
    static u16 m_upnp_mapped;
    static bool m_upnp_inited;
    static bool m_upnp_error;
    static std::thread m_upnp_thread;
#endif

    //override functions
    void OnTraversalStateChanged() override {}
    void OnConnectReady(ENetAddress address) override {}
    void OnConnectFailed(Common::TraversalConnectFailedReason reason) override {}
    void OnTtlDetermined(u8) override {}
  };
}