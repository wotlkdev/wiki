---
layout: default
title: Core Network
nav_order: 8
---

## Core Network

_Opcodes_ in WoW servers refers to the types of packets that the server and client can send to each others. These opcodes all come from reverse-engineering the packets exchanged between Blizzards official servers and the World of Warcraft client, meaning it is very hard (and rarely feasible) to change their structure or even what data they should contain.

All opcodes in the game are defined in [Opcodes.h](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Server/Protocol/Opcodes.h#:~:text=enum%20Opcodes), and have three common prefixes:
- `MSG_`: Means that the packet is sent both by the server to the clients, and from the clients to the server.
    - For example, movement packets like `MSG_MOVE_START_FORWARD` and `MSG_MOVE_STOP`

- `CSMG_`: Means that the packet is sent by the client to the server

- `SMSG_`: Means that the packet is sent by the server to the client

Both inbound and outbound packets in the game are represented by the [WorldPacket](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Server/WorldPacket.h#:~:text=class%20WorldPacket) class, which is just a basic class that can read and write data from a raw binary buffer.

### Sending Packets

When the server sends a packet to the client, it will construct a WorldPacket instance and send it to players usually by any of the following methods:

- [Player::SendDirectMessage](): Packets sent to a single player
- [Object::SendMessageToSet](): Packets sent to players around a `WorldObject`.
- [Map::SendToPlayers](): Packets sent to all players in a `Map`.

### Receiving Packets

The server has can handle incoming packets in one of three [PacketProcessing](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Server/Protocol/Opcodes.h#:~:text=enum%20PacketProcessing) phases:

- **Inplace**: Packets handled directly on the network thread, cannot access much of the game world at all and mostly used for unhandled packets.
- **ThreadUnsafe**: Packets that need to be handled in the main thread inside [World::UpdateSessions]().
- **ThreadSafe**: Packets that can be handled multithreaded in [Map::Update]().

There are also various rules deciding for what [SessionStatus](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Server/Protocol/Opcodes.h#:~:text=enum%20SessionStatus) the player must have for packets to be accepted:

- **Authed**: Packet is accepted once the player has authenticated but not entered the game world.

- **Logged In**: Packet is accepted if the player has entered the game world.

- **Transferring**: Packet is accepted if the player is currently transferring to another map.

- **Logged In or recently logged out**: Packet is accepted even if player logged out just recently

- **Never / Unimplemeted**: Packet is not handled.

All incoming packet handlers 

Incoming packet handlers are all registered in [Opcodes.cpp](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Server/Protocol/Opcodes.cpp#:~:text=#define%20DEFINE_SERVER_OPCODE_HANDLER).

This registry has the format:

`DEFINE_HANDLER(<opcode>,<player_status>,<process_phase>,<handler_function>)`

Where: 
- **opcode**: refers to the numeric opcode as defined in `Opcodes.h`.
- **player_status**: refers to the required `SessionPlayers` to accept the packet
- **process_phase**: refers to what `PacketProcessing` phase should process the packet
- **handler_function**: is a function pointer to the function that should process the packet when the server can handle it.

For example, if we look at the opcode handler for `CMSG_CAST_SPELL`, we get the following properties:
- Player must be logged in to send this packet
- This packet can be processed in map updates.
- This packet is processed in [WorldSession::HandleSpellCastOpcode](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Handlers/SpellHandler.cpp#:~:text=void%20WorldSession::HandleCastSpellOpcode)