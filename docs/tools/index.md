---
layout: default
title: Tools
nav_exclude: true
---

# Tools

This is a list of modern tools used by modders.

## General

- [**MPQEditor**](http://www.zezula.net/en/mpq/download.html): Tool to view and edit MPQ archives the clients MPQ archives.

- [**FuckItUp**](https://model-changing.net/index.php?app=downloads&module=downloads&controller=view&id=96): Removes the listfiles from MPQs that makes it (slightly) harder for a novice to open them.
    - Please note that experienced modders can open more or less any MPQ archive in a few minutes.

- [**ReShade**](https://reshade.me/releases): Generic graphics injector used to run custom shaders in the WoTLK client, like color grading, bloom or ambient occlusion effects.
    - Note that 'depth buffer' effects currently do not work with WoTLKs builtin multisampling, which forces you to turn this off to use such effects.



## Models and Textures

- [**WoW Blender Studio (WBS)**](https://discord.gg/SBEDRXrSnd): A Blender plugin used to create and modify M2 and WMO files in Blender.

- [**WoWModelViewer (WMV)**](https://code.google.com/archive/p/wowmodelviewer/downloads?page=6): Tool used to view WMO and M2 models in the game, and is used by tools like Noggit and WBS as a 'model selector'.
    - For WoTLK modding, the preferred version to use is [r252](https://storage.googleapis.com/google-code-archive-downloads/v2/code.google.com/wowmodelviewer/WMV_Binary_v0701_r252_Win32_DevWork.zip).

- [**BLPConverter**](https://www.wowinterface.com/downloads/info14110-BLPConverter.html): Tool used to convert between BLP and other common file formats like PNG and JPG.
    - Has a GUI version [here](https://model-changing.net/index.php?app=downloads&module=downloads&controller=view&id=96)

- [**M2Mod**](https://bitbucket.org/suncurio/m2mod/downloads/): Tool and blender plugin to work with mesh data on animated M2 files (cannot edit animations).

- [**Multiconverter**](https://github.com/MaxtorCoder/MultiConverter): Tool used to retroport model files from modern versions of the game to WoTLK.

## Maps and Lighting

- [**Noggit**](https://github.com/wowdev/noggit3): The most commonly used map editor for WoTLK.
    - [**Noggit Red**](https://discord.gg/Tk2TpN8CaF): Separate version of 'normal' Noggit with improvements like an undo menu and asset browser.
    - **Noggit Mint**: Name used to refer to 'normal' Noggit as opposed to Noggit Red.

- [**adtcreator**](https://github.com/tswow/adt-creator/tree/1fa79991ecbd91eec9420f5ad7d3eb6a5af17ed6): Simple command-line tool used to create new maps (adts + wdt) from scratch.
    - Binary shipped as part of [TSWoW](https://github.com/tswow/tswow/releases/tag/build-791454e), but the binary `bin/adtcreator/adtcreator.exe` can be used independently.

- [**WoW Machinima Tool**](https://model-changing.net/index.php?app=downloads&module=downloads&controller=view&id=96): In-game tool used to rapidly preview light, cloud and shader settings. Very useful for trying things out before writing them to the Light dbc files.

## Data Editors

- [**WDBX**](https://github.com/WowDevTools/WDBXEditor): A DBC editor for WoTLK

- [**SpellEditor**](https://github.com/stoneharry/WoW-Spell-Editor): A DBC editor specifically tailored for working with Spells and related tables.

- [**FuTa**](https://model-changing.net/index.php?app=downloads&module=downloads&controller=view&id=96): Tool used for importing alpha maps for adt textures.
    - If you don't like the version linked, just google it instead.

## Reverse Engineering

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