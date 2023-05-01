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

## Modern Tools

- [**WoWModelViewer (WMV)**](https://code.google.com/archive/p/wowmodelviewer/downloads?page=6): Tool used to view WMO and M2 models in the game, and is used by tools like Noggit and WBS as a 'model selector'.
    - For WoTLK modding, the preferred version to use is [r252](https://storage.googleapis.com/google-code-archive-downloads/v2/code.google.com/wowmodelviewer/WMV_Binary_v0701_r252_Win32_DevWork.zip).


- [**BLPConverter**](https://www.wowinterface.com/downloads/info14110-BLPConverter.html): Tool used to convert between BLP and other common file formats like PNG and JPG.
    - Has a GUI version [here](https://model-changing.net/index.php?app=downloads&module=downloads&controller=view&id=96)

- [**M2Mod**](https://bitbucket.org/suncurio/m2mod/downloads/): Tool and blender plugin to work with mesh data on animated M2 files (cannot edit animations).

- [**Multiconverter**](https://github.com/MaxtorCoder/MultiConverter): Tool used to retroport model files from modern versions of the game to WoTLK.

- [**WoW Blender Studio (WBS)**](https://discord.gg/SBEDRXrSnd): A Blender plugin used to create and modify M2 and WMO files in Blender.

- [**Noggit**](https://github.com/wowdev/noggit3): The most commonly used map editor for WoTLK.
    - [**Noggit Red**](https://discord.gg/Tk2TpN8CaF): Separate version of 'normal' Noggit with improvements like an undo menu and asset browser.
    - **Noggit Mint**: Name used to refer to 'normal' Noggit as opposed to Noggit Red.

- [**WDBX**](https://github.com/WowDevTools/WDBXEditor): A DBC editor for WoTLK

- [**SpellEditor**](https://github.com/stoneharry/WoW-Spell-Editor): A DBC editor specifically tailored for working with Spells and related tables.

- [**adtcreator**](https://github.com/tswow/adt-creator/tree/1fa79991ecbd91eec9420f5ad7d3eb6a5af17ed6): Simple command-line tool used to create new maps (adts + wdt) from scratch.
    - Binary shipped as part of [TSWoW](https://github.com/tswow/tswow/releases/tag/build-791454e), but the binary `bin/adtcreator/adtcreator.exe` can be used independently.

- [**FuckItUp**](https://model-changing.net/index.php?app=downloads&module=downloads&controller=view&id=96): Removes the listfiles from MPQs that makes it (slightly) harder for a novice to open them.
    - Please note that experienced modders can open more or less any MPQ archive in a few minutes.

- [**WoW Machinima Tool**](https://model-changing.net/index.php?app=downloads&module=downloads&controller=view&id=96): In-game tool used to rapidly preview light, cloud and shader settings. Very useful for trying things out before writing them to the Light dbc files.

- [**ReShade**](https://reshade.me/releases): Generic graphics injector used to run custom shaders in the WoTLK client, like color grading, bloom or ambient occlusion effects.
    - Note that 'depth buffer' effects currently do not work with WoTLKs builtin multisampling, which forces you to turn this off to use such effects.

- [**FuTa**](https://model-changing.net/index.php?app=downloads&module=downloads&controller=view&id=96): Tool used for importing alpha maps for adt textures.
    - If you don't like the version linked, just google it instead.

- [**010 Editor**](https://www.sweetscape.com/010editor/): A 'hex editor' used to view and edit binary files or executables.
    - 010 Templates: scripts written in 010 editor to **visualize** common file formats in WoW.
    - 010 Scripts: scripts written in 010 editor to automate tasks with binary files.
    - [Collection of WoTLK 010 Templates and Scripts](https://github.com/skarndev/WoW-010-editor-scripts-templates.)

- [**IDA**](https://hex-rays.com/ida-pro/): A [disassembler](https://en.wikipedia.org/wiki/Disassembler) tool commonly used to reverse engineer and debug the wow.exe client.

- [**Ghidra**](https://github.com/NationalSecurityAgency/ghidra/releases): Another disassembler and free alternative to IDA.



## Legacy Tools

These are tools that should be avoided due to bugs or because there are much better tools around today.

- [**MyDBCEditor**](https://github.com/wowgaming/old-dbc-editors/releases/tag/1.0): A DBC editor for WoTLK
    - Prefer WDBX.

## Communities and Websites

- [**model-changing (mcnet)**](https://model-changing.net/): Website and discord community for WoW modding. Main hub for WoTLK modding today.

- [**Modcraft**](http://emudevs.modcraft-backup.de/index.php): Old website for wow modding, now just an archive for old tutorials and resources.

- [**ac-web**](https://ac-web.org/): Website and forum for wow emulation and modding, has a lot of repacks.

- [**OwnedCore**](https://www.ownedcore.com/): Website for modding, hacking and gold selling. Used to be a hub for wow modding and contains some useful old guides, but is not used very often anymore.

- [**wowdev.wiki**](https://wowdev.wiki/Main_Page): A website that documents many of WoWs binary file formats and database layouts for multiple versions of the game.