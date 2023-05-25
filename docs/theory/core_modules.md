---
layout: default
title: Core Modules
nav_order: 7
---

# Core Modules

The types of modules found in the core tend to fall into one of 5 general categories, **subsystem singletons**, **templates**, **objects**, **special entities** and **utility modules**.

## Subsystem Singletons

These are server-wide systems used to contain logic relating to specific parts of the game, such as Battlegrounds, Spells and Groups.
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

## Templates

Chunks of data used to define _types_ (not instances) of creatures, quests, spells, achievements, game objects, items and so on.

- Populated on startup from [DBC Files](./dbc) and static [Database tables](./database).
- Are usually in files close to the _Entities_ that they describe.
- Not to be confused with [C++ templates](https://www.learncpp.com/cpp-tutorial/template-classes/)
- Have inconsistent naming, are sometimes named things like `<X>Template`, `<X>Info`, `<X>Data` and so on, where `<X>` denotes the type, like `Spell`, `Quest`, `Item` and so on.
- Examples (not exhaustive):
    - [SpellInfo](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Spells/SpellInfo.h#:~:text=class%20TC_GAME_API%20SpellInfo) (From [Spell.dbc](../dbc/Spell))
    - [CreatureTemplate](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Entities/Creature/CreatureData.h#:~:text=struct%20TC_GAME_API%20CreatureTemplate) (From database table [creature_template](https://trinitycore.atlassian.net/wiki/spaces/tc/pages/1200128167/creature+template+3.3.5a))
    - [GameObjectTemplate](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Entities/GameObject/GameObjectData.h#:~:text=struct%20GameObjectTemplate) (From database table [gameobject_template](https://trinitycore.atlassian.net/wiki/spaces/tc/pages/2130143/gameobject+template))
    - [ItemTemplate](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Entities/Item/ItemTemplate.h#:~:text=struct%20TC_GAME_API%20ItemTemplate) (From database table [item_template](https://trinitycore.atlassian.net/wiki/spaces/tc/pages/2130222/item+template) and [Item.dbc](../dbc/Item))

## Special Entities

Gameplay entities that are not templates and don't fit into the primary entity type hierarchy.
- Examples (not exhaustive):
    - [Spell](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Spells/Spell.h#:~:text=class%20TC_GAME_API%20Spell)
    - [Aura](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Spells/Auras/SpellAuras.h#:~:text=class%20TC_GAME_API%20Aura)
    - [Map](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Maps/Map.h#:~:text=class%20TC_GAME_API%20Map)
    - [Vehicle](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Entities/Vehicle/Vehicle.h#:~:text=class%20TC_GAME_API%20Vehicle)

## Utility Modules

Various other classes and files in the core that don't fit any of the above categories, such as the [worldserver main function](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/worldserver/Main.cpp) and [Database classes](https://github.com/TrinityCore/TrinityCore/tree/3.3.5/src/server/database/Database).

## Objects

One of the most important classes in the core is the [Object](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Entities/Object/Object.h#:~:text=class%20TC_GAME_API%20Object) class. This class is the base type for most types of entities in the game, such as `Players`, `Creatures`, `GameObjects` and even `Items`.

The object class itself do not contain a lot of logic, aside from some basic functions to interact with special fields called _UpdateData_ fields.

### UpdateData

To understand the Object type hierarchy, we need to first understand what UpdateData is. The World of Warcraft client has a special protocol for exchanging information about entities in the world known colloquially as _UpdateData_. This is a big chunk of binary data that propagate changes from the server to the client every world update to inform it about changes in various information about entities, such as player and creature health, mana and other stats.

Some updatedata fields, like hp, are _public_, meaning that players close to them will be informed about these fields changing, while others are _private_, such as players quest status, meaning that they are only sent to a specific player or set of players depending on some logic.

This binary chunk of data that the client expects is constructed as a type hierarchy, where different types of entities have _some_ updatedata fields in common, such as hp for players and creatures, while they have some that are unique to them, such as the questlog for players.

This type hierarchy is what lays the foundation for the `Object` type hiearchy used by the core, which is why it's important to understand UpdateData to understand why the core has the entity types that it does.

All names used for UpdateData fields can be found in [UpdateFields.h](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Entities/Object/Updates/UpdateFields.h). Because these are derived from the client itself, it is not possible (feasible) to modify them or add new updatedata fields.

<img class="mi ili" src = "https://i.imgur.com/uE0jMdQ.png">


The offsets provided in this header is then used by the `SetXValue()` methods found in the `Object` class, such as `SetUInt32()` and `SetUInt8()` to modify the updatedata attached to that entity.
- For example, changing a players [title](../dbc/CharTitles.dbc) would look like this:
    - `player->SetUInt32(PLAYER_CHOSEN_TITLE, TITLE_ID)`

### Object Type Hierarchy

Now that we understand the structure of UpdateData, we can discuss the type hierarchy used to define entities in the game world. The most important types that most developers should know about are marked as bold. Note that not every subclass used in cores have corresponding fields in UpdateData, and it's mostly the basic types that do.

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

## Core Spells

The spell system is a very complex system that controls much of the behavior exhibited by `Objects`, and depends on data found in both DBC files and server database. The most important of these being [Spell.dbc](../dbc/Spell). This section will not explain the entire spell system in detail, but should give a general outline of the classes involved and some of the most important phases and functions used for them.

### Spell Types

The most important core types used to represent spells are the following:

- [SpellInfo](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Spells/SpellInfo.h#:~:text=class%20TC_GAME_API%20SpellInfo): Represents a static _template_ for a **type** of spell. For examples, contains all the fields that define how spells like `Firebolt` behave, but is not tied to any specific spellcast in the world. This is (for the most part) the in-memory representation of an entry in [Spell.dbc](../dbc/Spell).

- [Spell](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Spells/Spell.h#:~:text=class%20TC_GAME_API%20Spell): Represents a single spellcast from start to finish
    - For example, when casting firebolt, a `Spell` object is created the moment that the Unit begins casting, and is destroyed when the spell missile hits its target.

- [Aura](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Spells/Auras/SpellAuras.h#:~:text=class%20TC_GAME_API%20Aura): The equivalent to `Spell` for persistent auras (buffs/debuff), and represents the persistent form of a spellcast.
    - Despite its name, Auras refer to **all** kinds of visible and invisible persistent effects, buffs and debuffs, and not only proper auras like _Devotion Aura_, though that is also a type of Aura.

- [AuraApplication](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Spells/Auras/SpellAuras.h#:~:text=class%20TC_GAME_API%20AuraApplication): Represents the application of an `Aura` on a single target. Some auras, like AoE auras, have multiple targets, and an AuraApplication represents that auras application on a specific `Unit`.

- [AuraEffect](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Spells/Auras/SpellAuraEffects.h#:~:text=class%20TC_GAME_API%20AuraEffect): Represents various effects active on a single `Aura`, such as periodic damage effects or stat debuffs. A single `Aura` can have multiple `AuraEffects` attached to it.
    - Note that AuraEffects belong to the `Aura` instance, and are not unique to individual `AuraApplications`.