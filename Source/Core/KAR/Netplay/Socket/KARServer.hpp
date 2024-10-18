#pragma once

//defines a server for KAR Matches

#include "Common/TraversalClient.h"
#include "Core/NetPlayProto.h"
#include "Common/Timer.h"

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
    void Init();

    //shutsdown the server
  };
}