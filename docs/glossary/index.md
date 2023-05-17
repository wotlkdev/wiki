---
layout: default
title: Glossary
nav_exclude: true
---

# Glossary

terms and such

## General Terms

- **Emulator/Core**: Refers to software used to run a private server, like TrinityCore or AzerothCore. 
    - **Emulator** is typically used to underline the servers function to _emulate_ the game, like how you would emulate a video game console.
    - **Core** is typically used more specifically to refer to the internal C++ code used to run the server itself, as opposed to scripts or the games database.

- **authserver/realmd**: This is the part of the core that handles initial connections to the server, and presents the realmlist when a player connects for the first time.
    - **realmd** is the name for this program in MaNGOS
    - **authserver** is the name for this program in TrinityCore and its derivatives.
    - Despite its TrinityCore-derived name, this program does not actually authenticate the player to the gameserver itself, but simply authenticates them to show the realmlist. Gameserver authentication happens on the worldserver, not the 'authserver'.

- **worldserver/mangosd**: This is the actual gameserver part of the core.
    - **mangosd** is the name for this program in MaNGOS.
    - **worldserver** is the name for this program in TrinityCore and its derivatives.

- **Dupe**: A very serious bug that allows players to duplicate money or items.

- **Crash**: When a program abruptly shuts down due to an error.

- **Crash log**: A special file that a program can produce when it crashes. For wow servers, crashlogs are typically found in the `Crashes` subdirectory where your `worldserver.exe` is located.

- **Fork**: Refers to a project that has branched out from another project and created a new version of it, like Noggit Red from Noggit or AzerothCore from TrinityCore.

- **GPL**: A software license that demands that you publish the source code for all your modifications and additions if you distribute compiled binaries (e.g. repacks).

- **AGPL**: A more strict version of the GPL that **also** demands that you publish the source code for all your modifications and additions if you **host a server**.

- **Retroporting**: Taking content or assets from modern versions of the game and making them work with an older version such as WoTLK.

## File formats

- **BLP**: Image file format used by WoTLK, used for virtually all textures and images in the game.

- **DBC** - Client data tables that contains game data for a lot of different things in the game, like Spells, Classes, Races and much more. Can be edited with WDBX:
    - Can be edited with WDBX or TSWoW.

- **MPQ** - Special archive files (like zip files) used by the WoTLK client to store client game data.
    - Can be edited with MPQEditor.
    - **Listfile**: Refers to text files that lists all the filenames that exists in the MPQ archive. Can be either shipped with the MPQ archive itself or added externally in MPQEditor.

### 3D Models

- **M2**: - Model files used for characters, creatures, spells, items and props.
    - Can be edited with WBS.

- **Skin**: File that compliments an **M2** file with different level-of-detail (LOD) profiles.

- **WMO**: Model files used for houses, caves, capitals.
    - Can be edited with WBS.
    - **WMO Root File**: The 'main' WMO file without any **_xxx** extension.
    - **WMO Group File**: File that compliments a wmo root file, and has an **_xxx** extension in its name.

### Map Files

- **ADT**: Map terrain files that store terrain heightmaps, texture data and placed props in the world. Can be edited with Noggit.
    - Can be edited with Noggit
    - **Alpha Maps**: Refers to the layers of textures on the terrain in an ADT.

- **WDT**: A single file for each map in the game used to define what **.adt** files are supposed to exist for that map.

- **WDL**: A single file for each map that contains a low-res heightmap used to display far-away mountains.

### Interface / Scripting

- **Lua**: A scripting language used in the WoW client to create interfaces and AddOns, and sometimes on servers to create scripts.

- **XML**: A file used in client to create interfaces and AddOns along with Lua files. XML files usually define the _layout_ of the client interface, while Lua files define its _behavior_.
