---
layout: default
title: Core Game Loop
nav_order: 6
---

# Core Game Loop

The worldserver executable has three primary phases: initialization, game loop, shutdown and then the fourth in the crash handler. The execution flow of the primary phases are relatively straightforward, while the crash handler is a special procedure that is only called when something goes wrong.

<img class="mi ili" src="https://i.imgur.com/M25FjTR.png">

## Initialization

<img class="mi ili" src="https://i.imgur.com/ZyhkwHU.png">

The initialization is handled through primarily two functions, `main` and `World::SetInitialWorldSettings`, which themselves call tons of other smaller functions for initializing specific subsystems.

- [int main](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/worldserver/Main.cpp#:~:text=int%20main): Starts up threads, freeze detector and other handles
    - [World::SetInitialWorldSettings](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/World/World.cpp#:~:text=void%20World::SetInitialWorldSettings()): Loads DBC data, static database data, scripts and initializes gameplay-related systems.
        - [World::LoadConfigSettings](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/World/World.cpp#:~:text=void%20World::LoadConfigSettings(bool%20reload)): Loads configuration files (worldserver.conf) into the Configuration Manager.

## Game Loop
<img class="mi ili" src="https://i.imgur.com/ycTFXZq.png">

The main game loop is the phase that handles what happens to the world as players enter it, reacting to network packets, moving entities around, executing combat and so on. 

The game loop is itself divided into three primary phases:

- **Early Updates**: Various global things like cleanup, who lists etc.
- **Map Updates**: Updates individual maps (Kalimdor, Eastern Kingdoms, Outland, Instances, Battlegrounds etc)
    - **Primary Map Updates**: Multithreaded, where almost all game logic happens
    - **Delayed Map Updates**: Single-threaded, handles minor things like moving transports and cross-map spells
- **Late Updates**: Handles various things like groups, guilds and channels.

### Callstack outline

This is an outline of some of the most important functions involved in the game loop. The call stack is not exact, but is mostly meant to allow easily visualize roughly in what orders things happen in the server.

- [main](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/worldserver/Main.cpp#:~:text=int%20main) - Main function of the program
    - [WorldUpdateLoop](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/worldserver/Main.cpp#:~:text=int%20main) - Self-sustaining loop that handles update time differences and ensures updates don't fire too frequently.
        - [World::Update](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/World/World.cpp#:~:text=void%20World::Update(uint32%20diff)) - Root function for a updating a single tick of the game world. Aside from map updates and occasional use of worker threads, this function is single-threaded.
            - Early Updates:
                - who list
                - calendar events
                - auctions,
            - [MapManager::Update](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Maps/MapManager.cpp#:~:text=void%20MapManager::Update(uint32%20diff)): Updates all maps loaded into the game
                - Normal Phase: (optionally) multithreaded map updates
                    - [Map::Update](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Maps/Map.cpp#:~:text=void%20Map::Update(uint32%20t_diff)): Primary function used to update a single map, may run in isolated threads
                        - [Unit::Update](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Entities/Unit/Unit.cpp#:~:text=void%20Unit::Update(uint32%20p_time)): Generic update function for all units
                        - [Player::Update](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Entities/Player/Player.cpp#:~:text=void%20Player::Update(uint32%20p_time)): Update function specific to players
                        - [Creature::Update](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Entities/Creature/Creature.cpp#:~:text=void%20Creature::Update(uint32%20diff)): Update function specific to non-player units
                        - [Map::MoveAllCreaturesInMoveList](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Maps/Map.cpp#:~:text=void%20Map::MoveAllCreaturesInMoveList()): Handles creature movement
                        - [Map::MoveAllGameObjectsInMoveList](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Maps/Map.cpp#:~:text=void%20Map::MoveAllGameObjectsInMoveList()): Handles transport (boats, zeppelins) movement
                        - [Map::SendObjectUpdates](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Maps/Map.cpp#:~:text=void%20Map::SendObjectUpdates()): Broadcasts 'UpdateData' packets. One of the slowest functions in the map update.
                        - [Map::ProcessRelocationNotifies](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Maps/Map.cpp#:~:text=void%20Map::ProcessRelocationNotifies(const%20uint32%20diff)): Main function for handling visibility updates
                - Delayed Phase: Map update logic that needs to run on the main thread (not multithreaded)
                    - [Map::DelayedUpdate](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Maps/Map.cpp#:~:text=void%20Map::DelayedUpdate(uint32%20t_diff)): Updates a single map on the main thread
                        - Handles cross-map spells
                        - Moves transports between maps
                        - Removes objects
            - Late Updates
                - [BattlegroundMgr::Update](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Battlegrounds/BattlegroundMgr.cpp#:~:text=void%20BattlegroundMgr::Update(uint32%20diff)): Updates all battlegrounds
                    - [Battleground::Update](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Battlegrounds/Battleground.cpp#:~:text=void%20Battleground::Update(uint32%20diff)): Updates a single battleground
                - [OutdoorPvPMgr::Update](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/OutdoorPvP/OutdoorPvPMgr.cpp#:~:text=void%20OutdoorPvPMgr::Update(uint32%20diff)): Updates logic for all outdoor pvp (tower captures etc)
                    - [OutdoorPvP::Update](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/OutdoorPvP/OutdoorPvP.cpp#:~:text=bool%20OutdoorPvP::Update(uint32%20diff)): Updates a single OutdoorPvP script
                - [BattlefieldMgr::Update](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Battlefield/BattlefieldMgr.cpp#:~:text=void%20BattlefieldMgr::Update(uint32%20diff)): Updates battlefields like wintergrasp
                    - [Battlefield::Update](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Battlefield/Battlefield.cpp#:~:text=bool%20Battlefield::Update(uint32%20diff)): Updates a single battlefield
                - [GroupMgr::Update](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Groups/GroupMgr.cpp#:~:text=void%20GroupMgr::Update(uint32%20diff)): Updates all partys and raids
                    - [Group::Update](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Groups/Group.cpp#:~:text=void%20Group::Update(uint32%20diff))
                - [LfgMgr::Update](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/DungeonFinding/LFGMgr.cpp#:~:text=void%20LFGMgr::Update(uint32%20diff)): Updates the LFG queue
                - [GameEventMgr::Update](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Events/GameEventMgr.cpp#:~:text=uint32%20GameEventMgr::Update()): Updates game and holiday events like the fishing derby or brewfest.
                - [World::ProcessCliCommands](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/World/World.cpp#:~:text=void%20World::ProcessCliCommands()): Handle input to the worldserver console window

## Multithreading

The primary use of multithreading that is relevant to most developers is the worker threads handling map updates, but these are not the only instances of threading in the core.

Threads are also used to handle various other things in parallel to the primary game loop such as:
- **Network connections / Packet handlers**
- **Database queries** and utility
- Freeze detection
- Crash handling

Developers _usually_ do not need to worry about these the way they need to worry about threaded map updates unless they stumble into them, primarily relating to **database connections**.