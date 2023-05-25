---
layout: default
title: Core Code Structure
nav_order: 5
---

# Core Code Structure

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
            - [shared](https://github.com/TrinityCore/TrinityCore/tree/3.3.5/src/server/database): Similar to the [common](https://github.com/TrinityCore/TrinityCore/tree/3.3.5/src/common) library, but more specifically for authserver/worldserver stuff.
            - [**scripts**](https://github.com/TrinityCore/TrinityCore/tree/3.3.5/src/server/scripts): Code used to script specific behavior in the game, such as very specific spells, dungeon bosses, instances, battlegrounds and chat commands.
            - [**game**](https://github.com/TrinityCore/TrinityCore/tree/3.3.5/src/server/game): Contains all primary game logic, by far the most important directory in the entire core.
                - Usually split into various modules and subsystems, see [Core Modules](./core_modules).