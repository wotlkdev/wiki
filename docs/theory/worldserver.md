---
layout: default
title: Worldserver
nav_order: 1
---

# Worldserver

This article will contain a surface-level explanation and introduction to how the worldserver works and how you can navigate its source code.

It is not meant to be an all-encompassing technical outline, as the worldserver is far too complex to even begin to explain in a single article. Being able to navigate complex source code is an important skill to be able to master the worldserver, but this document might help get beginners started to know where to start looking for the most important parts.

## Code References

The vast majority of this article should be applicable to any modern core as they are all very similar to each others, but is primarily based on TrinityCore.

Code references will attempt to find function names by text, occasionally links might not work and will require some additional searching. Rarely, function names listed here may become outdated and need updating.

**Note: These code links don't seem to work on firefox, but do work on chrome.**

## Repository Structure

Most cores follow the exact same file structure, with only minor variations.

<img src="https://i.imgur.com/lWa1Aa6.png">

_For TSWoW, the core is not stored in the [root repository](https://github.com/tswow/tswow), but inside a [submodule](https://github.com/tswow/tswow/tree/master/cores) that contains the same structure as a normal core._

- [Repository Root](https://github.com/TrinityCore/TrinityCore/): readme, licensing information, entrypoint for [CMake](https://github.com/TrinityCore/TrinityCore/blob/master/CMakeLists.txt) and various other configuration files.
    - [.circleci](https://github.com/TrinityCore/TrinityCore/tree/3.3.5/.circleci)/[.github](https://github.com/TrinityCore/TrinityCore/tree/master/.github): Scripts relating to building the core automatically on the GitHub repository.
        - _Rarely relevant for developers_
    - [cmake](https://github.com/TrinityCore/TrinityCore/tree/3.3.5/cmake): Scripts relating to setting up the build system and finding libraries that the core depends on.
        - _Occasionally relevant for developers_
    - [contrib](https://github.com/TrinityCore/TrinityCore/tree/3.3.5/contrib) : Various other scripts 
        - _Rarely relevant for developers_
    - [dep](https://github.com/TrinityCore/TrinityCore/tree/3.3.5/dep): Third-party libraries that ship with the core, rarely touched
    - [doc](https://github.com/TrinityCore/TrinityCore/tree/3.3.5/doc): Old documentation, rarely touched
    - [**sql**](https://github.com/TrinityCore/TrinityCore/tree/3.3.5/sql): SQL files used to set up the servers [databases](./database)
    - [tests](https://github.com/TrinityCore/TrinityCore/tree/3.3.5/tests): Automatic tests
    - [**src**](https://github.com/TrinityCore/TrinityCore/tree/3.3.5/src): The actual server source code
        - [common](https://github.com/TrinityCore/TrinityCore/tree/3.3.5/src/common): Code used across multiple components in the core, such as cryptography functions, logging and networking.
        - [genrev](https://github.com/TrinityCore/TrinityCore/tree/3.3.5/src/genrev): A single cmake script used to generate revision information from the git repository.
        - [tools](https://github.com/TrinityCore/TrinityCore/tree/master/src/tools): Code for DBC/Map/VMAP/MMAP extractors
        - [**server**](https://github.com/TrinityCore/TrinityCore/tree/3.3.5/src/server): Code used for the worldserver/authserver.
            - [authserver](https://github.com/TrinityCore/TrinityCore/tree/3.3.5/src/server/authserver): Code building the authserver executable
            - [worldserver](https://github.com/TrinityCore/TrinityCore/tree/3.3.5/src/server/worldserver): Code building the worldserver executable (does not contain gameplay code)
            - [database](https://github.com/TrinityCore/TrinityCore/tree/3.3.5/src/server/database): Code used for interacting with the database (used by both authserver and worldserver)
            - [shared](https://github.com/TrinityCore/TrinityCore/tree/3.3.5/src/server/database): Similar to the [common](https://github.com/TrinityCore/TrinityCore/tree/3.3.5/src/common) library, but often more specifically for authserver/worldserver stuff.
            - [**scripts**](https://github.com/TrinityCore/TrinityCore/tree/3.3.5/src/server/scripts): Code used to script specific behavior in the game, such as very specific spells, dungeon bosses, instances, battlegrounds and chat commands.
            - [**game**](https://github.com/TrinityCore/TrinityCore/tree/3.3.5/src/server/game): Contains all primary game logic, by far the most important directory in the entire core.
                - Usually split into various modules and subsystems, see the below section on "Core Modules".

## Execution Graph

The worldserver executable has three (four) main phases: initialization, game loop, shutdown and crash handler. The execution flow of the primary phases are relatively straightforward, while the crash handler is a special procedure that is only called when something goes wrong.

<img src="https://i.imgur.com/M25FjTR.png">

## Initialization

<img src="https://i.imgur.com/ZyhkwHU.png">

The initialization is handled through primarily two functions, `main` and `World::SetInitialWorldSettings`, which themselves call tons of other smaller functions for initializing specific subsystems.

- [int main](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/worldserver/Main.cpp#:~:text=int%20main): Starts up threads, freeze detector and other handles
    - [World::SetInitialWorldSettings](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/World/World.cpp#:~:text=void%20World::SetInitialWorldSettings()): Loads DBC data, static database data, scripts and initializes gameplay-related systems.
        - [World::LoadConfigSettings](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/World/World.cpp#:~:text=void%20World::LoadConfigSettings(bool%20reload)): Loads configuration files (worldserver.conf) into the Configuration Manager.

## Game Loop
<img src="https://i.imgur.com/ycTFXZq.png">

The main game loop is the phase that handles what happens to the world as players enter it, reacting to network packets, moving entities around, executing combat and so on. 

The game loop is itself divided into three primary phases:

- **Early Updates**: Handles various things mostly related to cleaning up
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
                        - [Unit::Update](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Entities/Unit/Unit.cpp:~:text=void%20Unit::Update(uint32%20p_time)): Generic update function for all units
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

## Core Modules

The types of modules found in the core tend to fall into one of 5 general categories:

- **Subsystem Singletons**: Server-wide systems used to contain logic relating to specific parts of the game, such as Battlegrounds, Spells and Groups.
    - Singleton modules are classes that only have **one** instance in the entire program.
    - Singleton modules often have the responsibility of _initializing_ subsystems, as well as _containing_ and _updating_ various **instance classes**.
    - Exactly what singleton modules actually do varies between modules, and requires reading the individual subsystem. There's no general rule here.
    - Singletons are typically stored in `<X>/<X>Mgr.h` files, and have the class name `<X>Mgr` with an instance variable named `s<X>Mgr`, where `<X>` is the name of the module.
    - For example, the singleton class [SpellMgr](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Spells/SpellMgr.h#:~:text=class%20TC_GAME_API%20SpellMgr) is accessed through the global instance variable name [sSpellMgr](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Spells/SpellMgr.h#:~:text=#define%20sSpellMgr%20SpellMgr::Instance()).
    - Not all types of instance classes have their own manager singleton, and some entities like `Players` and `Creatures` are instead managed by Maps and in Map updates.
    - Examples (not exhaustive):
        - [AccountMgr](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Accounts/AccountMgr.h)
        - [AchievementMgr](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Achievements/AchievementMgr.h)
        - [AuctionHouseMgr](https://github.com/TrinityCore/TrinityCore/tree/3.3.5/src/server/game/AuctionHouse)
        - [MapManager](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Maps/MapManager.h)
        - [GroupMgr](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Groups/GroupMgr.h)
        - [GuildMgr](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Guilds/GuildMgr.h)
        - [LootMgr](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Loot/LootMgr.h)

- **Templates**: Chunks of data used to define _types_ (not instances) of creatures, quests, spells, achievements, game objects, items and so on.
    - Populated on startup from [DBC Files](./dbc) and static [Database tables](./database).
    - Are usually in files close to the _Entities_ that they describe.
    - Not to be confused with [C++ templates](https://www.learncpp.com/cpp-tutorial/template-classes/)
    - Have inconsistent naming, are sometimes named things like `<X>Template`, `<X>Info`, `<X>Data` and so on, where `<X>` denotes the type, like `Spell`, `Quest`, `Item` and so on.
    - Examples (not exhaustive):
        - [SpellInfo](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Spells/SpellInfo.h#:~:text=class%20TC_GAME_API%20SpellInfo) (From [Spell.dbc](../dbc/Spell))
        - [CreatureTemplate](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Entities/Creature/CreatureData.h#:~:text=struct%20TC_GAME_API%20CreatureTemplate) (From database table [creature_template](https://trinitycore.atlassian.net/wiki/spaces/tc/pages/1200128167/creature+template+3.3.5a))
        - [GameObjectTemplate](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Entities/GameObject/GameObjectData.h#:~:text=struct%20GameObjectTemplate) (From database table [gameobject_template](https://trinitycore.atlassian.net/wiki/spaces/tc/pages/2130143/gameobject+template))
        - [ItemTemplate](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Entities/Item/ItemTemplate.h#:~:text=struct%20TC_GAME_API%20ItemTemplate) (From database table [item_template](https://trinitycore.atlassian.net/wiki/spaces/tc/pages/2130222/item+template) and [Item.dbc](../dbc/Item))

- **Objects**: The primary type hierarchy that most entities in the world belongs to, such as _Players_, _Items_, _Creatures_ and _GameObjects_ (see below section on Objects).

- **Special Entities**: Gameplay entities that are not templates and don't fit into the primary entity type hierarchy.
    - Examples (not exhaustive):
        - [Spell](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Spells/Spell.h#:~:text=class%20TC_GAME_API%20Spell)
        - [Aura](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Spells/Auras/SpellAuras.h#:~:text=class%20TC_GAME_API%20Aura)
        - [Map](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Maps/Map.h#:~:text=class%20TC_GAME_API%20Map)
        - [Vehicle](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Entities/Vehicle/Vehicle.h#:~:text=class%20TC_GAME_API%20Vehicle)

- **Utility Modules**: Various other classes and files in the core that don't fit any of the above categories, such as the [worldserver main function](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/worldserver/Main.cpp) and most [Database classes](https://github.com/TrinityCore/TrinityCore/tree/3.3.5/src/server/database/Database).

## Objects

One of the most important classes in the core is the [Object](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Entities/Object/Object.h#:~:text=class%20TC_GAME_API%20Object) class. This class is the base type for most types of entities in the game.

The object class itself do not contain a lot of logic, aside from some basic functions to interact with special fields called _UpdateData_ fields.

### UpdateData

To understand the Object type hierarchy, we need to first understand what UpdateData is. The World of Warcraft client has a special protocol for exchanging information about entities in the world known colloquially as _UpdateData_. This is a big chunk of binary data sent from the server to the client every world update to inform it about various information about entities, such as player and creature health, mana and other stats, as well as their locations in the game world.

Some updatedata fields, like hp, are _public_, meaning that players close to them will be informed about these fields changing, while others are _private_, such as players quest status, meaning that they are only sent to a specific player or set of players depending on some logic.

This binary chunk of data that the client expects is constructed as a type hierarchy, where different types of entities have _some_ updatedata fields in common, such as hp for players and creatures, while they have some that are unique to them, such as the questlog for players.

This type hierarchy is what lays the foundation for the `Object` type hiearchy used by the core, which is why it's important to understand UpdateData to understand why the core has the entity types that it does.

All names used for UpdateData fields can be found in [UpdateFields.h](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Entities/Object/Updates/UpdateFields.h). Because these are derived from the client itself, it is not possible (feasible) to modify them or add new updatedata fields.

The offsets provided in this header is then used by the `SetXValue()` methods found in the `Object` class, such as `SetUInt32()` and `SetUInt8()` to modify the updatedata attached to that entity.
- For example, changing a players [title](../dbc/CharTitles.dbc) would look like this:
    - `player->SetUInt32(PLAYER_CHOSEN_TITLE, TITLE_ID)`

### Object Type Hierarchy

Now that we understand the structure of UpdateData, we can discuss the type hierarchy used to define entities in the game world. The most important types that most developers should know about are marked as bold.

- [Object](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Entities/Object/Object.h#:~:text=class%20TC_GAME_API%20Object): The root class for all types of entities already discussed
    - [**Item**](): Represents item instances that are stored in a players inventory, equipment slots or bank/guild bank.
        - Contains data like enchantments, random suffixes (of the Falcon, of the Boar etc.), mail text and player creation information.
    - [WorldObject](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Entities/Object/Object.h#:~:text=class%20TC_GAME_API%20WorldObject): Represents an object that can be spawned into the world directly and contains mostly location data.
        - [Corpse](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Entities/Corpse/Corpse.h#:~:text=class%20TC_GAME_API): Represents a dead lootable creature or resurrectable player, or their bones after decay.
        - [Unit](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Entities/Unit/Unit.h#:~:text=class%20TC_GAME_API%20Unit): Represents an object that has basic stats and combat capabilities
            - [**Creature**](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Entities/Creature/Creature.h#:~:text=class%20TC_GAME_API%20Creature): Represents all non-player Units in the world
                - [TempSummon](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Entities/Creature/TemporarySummon.h#:~:text=class%20TC_GAME_API%20TempSummon): Represents all types of temporary summons and pets in the game.
                    - The exact logic to select what class a temporary summon should use is mostly found in [Map::SummonCreature](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Entities/Object/Object.cpp#:~:text=Map::SummonCreature), and largely depends on data found in [SummonProperties.dbc](../dbc/SummonProperties)
                    - [Minion](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Entities/Creature/TemporarySummon.h#:~:text=class%20TC_GAME_API%20Minion): Used by subtypes or for various npc summons and companion pets
                        - [Totem](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Entities/Totem/Totem.h#:~:text=class%20TC_GAME_API%20Totem): Shaman totems
                        - [Guardian](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Entities/Creature/TemporarySummon.h#:~:text=class%20TC_GAME_API%20Guardian): Subtypes, guardian pets or some npc summons
                            - [Pet](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Entities/Pet/Pet.h#:~:text=class%20TC_GAME_API%20Pet): Hunter/Mage/Warlock pets
                    - [Puppet](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Entities/Creature/TemporarySummon.h#:~:text=class%20TC_GAME_API%20Puppet): Used for creatures that are controlled by a player, such as special mounts used in quests/dungeons (the kind of mounts you can select) and some vehicles.

            - [**Player**](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Entities/Player/Player.h#:~:text=class%20TC_GAME_API%20Player): Represents a player character in the world
        - [**GameObject**](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Entities/GameObject/GameObject.h#:~:text=class%20TC_GAME_API%20GameObject): Represents a large variety of object types, such as chairs, doors, chests, fishing bobs, flagpoles and so on.
            - [Transport](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Entities/Transport/Transport.h#:~:text=class%20TC_GAME_API%20Transport): Boats/zeppelins
        - [DynamicObject](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Entities/DynamicObject/DynamicObject.h#:~:text=class%20TC_GAME_API%20DynamicObject): Used for persistent AoE spells like Volley, Blizzard, Flame Strike etc.

    

## Spells

The spell system is a very complex system that controls much of the behavior exhibited by `Objects`, and depends on data found in both DBC files and server database. The most important of these being [Spell.dbc](../dbc/Spell). This section will not explain the entire spell system in detail, but should give a general outline of the classes involved and some of the most important phases and functions used for them.

### Types

The most important core types used to represent spells are the following:

- [SpellInfo](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Spells/SpellInfo.h#:~:text=class%20TC_GAME_API%20SpellInfo): Represents a static _template_ for a **type** of spell. For examples, contains all the fields that define how spells like `Firebolt` behave, but is not tied to any specific spellcast in the world. This is (for the most part) the in-memory representation of an entry in [Spell.dbc](../dbc/Spell).

- [Spell](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Spells/Spell.h#:~:text=class%20TC_GAME_API%20Spell): Represents a single spellcast from start to finish
    - For example, when casting firebolt, a `Spell` object is created the moment that the Unit begins casting, and is destroyed when the spell missile hits its target.

- [Aura](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Spells/Auras/SpellAuras.h#:~:text=class%20TC_GAME_API%20Aura): The equivalent to `Spell` for persistent auras (buffs/debuff), and represents the persistent form of a spellcast.
    - Despite its name, Auras refer to **all** kinds of visible and invisible persistent effects, buffs and debuffs, and not only proper auras like _Devotion Aura_, though that is also a type of Aura.

- [AuraApplication](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Spells/Auras/SpellAuras.h#:~:text=class%20TC_GAME_API%20AuraApplication): Represents the application of an `Aura` on a single target. Some auras, like AoE auras, have multiple targets, and an AuraApplication represents that auras application on a specific `Unit`.

- [AuraEffect](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Spells/Auras/SpellAuraEffects.h#:~:text=class%20TC_GAME_API%20AuraEffect): Represents various effects active on a single `Aura`, such as periodic damage effects or stat debuffs. A single `Aura` can have multiple `AuraEffects` attached to it.
    - Note that AuraEffects belong to the `Aura` instance, and are not unique to individual `AuraApplications`.

## Packet Handling and Opcodes

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

## Scripts

Scripts are used to implement special behavior for specific spells, creatures, instances or commands, where the core cannot rely on generic behaviors that generalize to large groups of entities, such as spells or small groups of spells that have highly special behaviors that no other spells have.

All scripts in the core can be found in the [scripts](https://github.com/TrinityCore/TrinityCore/tree/3.3.5/src/server/scripts) directory in the core repository. Here, scripts are divided into some generic categories that all have roughly the same format.

### Script Loading

Each script category contains a special _loader_ file, that usually has the format `<x>_script_loader.cpp`. For example:
- [battlefield_script_loader.cpp](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/scripts/Battlefield/battlefield_script_loader.cpp)
- [cs_script_loader.cpp](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/scripts/Commands/cs_script_loader.cpp)
- [**custom_script_loader.cpp**](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/scripts/Custom/custom_script_loader.cpp)
- [eastern_kingdoms_script_loader.cpp](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/scripts/EasternKingdoms/eastern_kingdoms_script_loader.cpp)
- [spell_script_loader.cpp](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/scripts/Spells/spell_script_loader.cpp)

These files all contain a single implemented function called `AddXScripts`, whose only purpose is to initialize all the other script files in the current folder. This function is itself called from an auto-generated file inside the core, depending on what scripts were defined to be compiled in the build settings.

When adding new script files with their own initialization functions, it is **necessary** to both add its function declaration to the corresponding `script_loader` file and also **call** that function inside the script loader function. Not doing this means the added script will not be loaded into the core.

### Script Structure

Most script consists of classes that contain **event handlers** and **virtual methods**, and are meant to be extended and implemented by specific script subclasses in the `scripts` folder.

Event handlers are registered in the scripts `Register` method, and can support multiple handlers in the same script, while **virtual methods** are meant to be implemented once by the script subclass. Basic examples of this will be provided below.

### Case study: Spell Scripts

Spell scripts are classes that inherit from the [SpellScript](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Spells/SpellScript.h#:~:text=class%20TC_GAME_API%20SpellScript) class.
- example virtual methods: 
    - [_SpellScript::Register](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Spells/SpellScript.h#:~:class%20TC_GAME_API%20virtual%20void%20Register): Used to register event handlers
    - [_SpellScript::Validate](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Spells/SpellScript.h#:~:text=virtual%20bool%20Validate): Used to ensure dbc/database related to the spell is correct

- example event handlers:
    - [_SpellScript::BeforeCast](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Spells/SpellScript.h#:~:text=Hooklist%3CCastHandler%3E%20BeforeCast)
    - [_SpellScript::OnCast](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Spells/SpellScript.h#:~:text=Hooklist%3CCastHandler%3E%20OnCast)
    - [_SpelScript::AfterCast](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Spells/SpellScript.h#:~:text=Hooklist%3CCastHandler%3E%20AfterCast)

For example, here is an implementation for a basic spell script class

```c++
#include "SpellScript.h"
#include <iostream>

class my_spell_script: public SpellScript
{
    // normal method, does not register to anything on its own
    void on_cast()
    {
        std::cout << "Hello world from my_spell_script\n";
    }

    // virtual function override
    void Register() override
    {
        // register on_cast to be an event handler
        OnCast += SpellCastFn(my_spell_cript::on_cast);
    }
}

// registry function (must be called manually from the script categories script loader!)
void AddSC_my_spell_scripts()
{
    RegisterSpellScript(my_spell_script);
}
```

To tie a specific spell id to a SpellScript, we use the server world database table [spell_script_names](https://trinitycore.info/en/database/335/world/spell_script_names), where the `ScriptName` column in that table maps to the class name we register in the `RegisterSpellScript` function. This allows the core to easily tie the same spell script to multiple spells without recompiling.

### Other Script Types

Other script types sometimes work similar to Spell scripts, like Aura scripts, while others like Creature scripts are sometimes nest classes of event handlers for more control in how to register behavior. It's usually enough to look at a couple of examples to understand how to implement them for new entities.