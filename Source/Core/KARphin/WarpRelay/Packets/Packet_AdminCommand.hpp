#pragma once

//defines a packet sent when executing a admin command

#include <SFML/Network/Packet.hpp>

#include <string>

namespace KARphin::WarpRelay::Netplay::Packet
{

// defines a admin command packet
struct Packet_AdminCommand
{
  uint8_t PID = 0; //who sent the commmand
  //what command was it
  std::string resultString = ""; //the result string of the command
};

// packs data into a packet we can send accros the network
static inline sf::Packet PackageDataIntoSFMLPacket_OnAdminCommand(const Packet_AdminCommand& data)
{
  sf::Packet packet;
  /*packet << (uint8_t)data.kind;
  packet << data.SCMVersion;
  packet << data.clientVersion;
  packet << data.nickname;
  packet << data.warpRelayIconURL;*/

  return packet;
}

// unpacks the recived pack into our custom data struct
static inline Packet_AdminCommand UnpackSFMLPacket_AdminCommand(sf::Packet& packet)
{
  Packet_AdminCommand data;
  packet >> data.PID;
  packet >> data.resultString;

  return data;
}
}  // namespace KARphin::WarpRelay::Netplay::Packet