---
layout: default
title: Client
nav_order: 10
---

# Client

This section will explain the various base-level components in the client, focusing on the folder structure and files that can be found in it.

## Layout

The client contains a variety of different folders and file formats that modders should be aware about

- Libraries: Code extensions and external code libraries used by wow.exe

- Cache: Creature/Item/Quest/Other information sent by the server and stored temporarily

- WTF: Options and AddOn save data

- Data: Game Assets, 3D models, Textures, Music, client databases (DBC).

<img src="https://i.imgur.com/dDknje3.png">

## Libraries (DLLs)

DLL files are special "code libraries" that executable programs (.exes) can load to gain additional functionality on the fly.

<img src="https://i.imgur.com/XGHxUwN.png">

### d3d9.dll

Normally, modders do not change anything in these files on their own, as they consist of compiled binary code that's generally hard to read for most people. The one common exception to this is `d3d9.dll`. This is the library file for DirectX9, which is the library that provides **graphics** for the game. Programs like `ReShade` or `d912pxy` replace this file with their own to support things like running under DirectX12 and add custom shaders.

<img src="https://i.imgur.com/vXRpLNy.png">



What may also be of interest to modders is hacking the client itself to load their own custom library, to allow easily injecting their own code into client via 'hooks' or 'detours'.

<img src="https://i.imgur.com/vqfauhU.png">

## Cache

The cache is a folder that temporarily stores serverside data to lessen the load on the network, such as creatures, items, quests and a few other things.

<img src="https://i.imgur.com/sH9aDB7.png">

When the client logs into the game and sees any of these things, it will first check if it recognizes any of them in its own cache, and if it doesn't ask the server to inform it about those things basic properties like stats and names.

<img src="https://i.imgur.com/roAZi1V.png">

### Dirty Cache

When playing the game on official servers, the cache rarely causes any issues since creature names and item stats rarely change outside of proper patches.

For modders, however, the cache can cause a lot of problems since we often change serverside data around a lot to try things out or because we change our minds.

It is, for this reason, always recommended to **delete the cache** whenever you are actively editing the game, which will force the client to always ask the server for **all** temporary data.

<img src="https://i.imgur.com/WY2uMcW.png">

Another option to keep the cache clean is to use an [edited wow.exe](https://model-changing.net/index.php?app=downloads&module=downloads&controller=view&id=9) that never loads the cache in the first place.

## WTF / Config

The `WTF` folder contains text files with all the options that can be set in the client, like graphics/sound/interface settings and keybindings. It also contains saved data for player macros and AddOn save data.

<img src="https://i.imgur.com/me7jERR.png">

## Data

The `Data` folder contains `MPQ` files, which is a type of zip archive that contains all the clients assets, persistent database tables and interface files.

The `Data` folder is itself split up between the _root_ folder and the _locale_ folder. The name of the locale folder varies between what localization of the game you have, but is usually called `enUS` or `enGB` for english clients.

<img src="https://i.imgur.com/eAIUwwk.png">

### MPQ Files

MPQ files are similar to large zip files that are used to contain asset data in older Blizzard games.

There are two important differences between MPQ files and normal zip files, **listfiles** and **file overriding**.

#### Listfiles

MPQ files do not map filenames to files the way most file systems and archive formats do, but instead map filename **hashes** to files. A hash is a type of one-way encryption that is impossible to reverse, but where the same input always produces the same output.

For example, the filename `DBFilesClient\\Spell.dbc` could map to the (fictional) hash `9128392831`. Everytime we fed the hash function the name `DBFilesClient\\Spell.dbc`, we would **always** get `9128392831`.

When the client asks MPQ archives for files, they run the filename it is looking for through the same hash function used to create the archive, and from that can find the file it was looking for by just looking up the hash.

MPQ files also contain what is called a "listfile", which is simply a text file that contains a bunch of filenames that should have hashes present in the archive. These listfiles is how editors like `MPQEditor` are able to open MPQ archives and present files and folders with real names despite that they are not actually stored with that data themselves, we just search for all the hashes we can produce from the listfile.

<img src="https://i.imgur.com/lvCWQm5.png">

Some modders choose to "protect" or "encrypt" their MPQ archives by removing this listfile, the game itself doesn't need it since it has its own internal set of filenames that it already knows how to encrypt.

When an MPQ archives has had its listfile deleted, editors like MPQEditor cannot know what filenames are actually contained in it, because there are no filenames present in the archive, only hashes.

<img src="https://i.imgur.com/QO8Tu9Z.png">

#### File Overriding

The other important feature of MPQ files is the clients ability to open multiple archives containing files with the same hashes and decide which file to actually load depending on an internal 'priority list' of what MPQ archives have higher priorities than others.

Unfortunately for modders, this priority list **differs between localizations**.

The load orders are as follows (higher numbers means higher priority):

**Russian/Chinese Clients (and possibly others)**

_(The order of non-patch files might be wrong here, but the order of patch archives is correct)_

1. "Base" non-patch files
2. "Base" numeric patch files (patch-1.MPQ to patch-9.MPQ in order)
3. "Base" alphabetic patch files (patch-A.MPQ to patch-Z.MPQ in order)
4. "Locale" non-patch files
5. "Locale" numeric patch files (patch-XX-1.MPQ to patch-XX-9.MPQ in order)
6. "Locale" alphabetic patch files (patch-XX-A.MPQ to patch-XX-Z.MPQ in order)

**English Clients**

1. "Locale" non-patch files
2. "Locale" numeric patch files (patch-XX-1.MPQ to patch-XX-9.MPQ in order)
3. "Locale" alphabetic patch files (patch-XX-A.MPQ to patch-XX-Z.MPQ in order)
4. "Base" non-patch files
5. "Base" numeric patch files (patch-1.MPQ to patch-9.MPQ in order)
6. "Base" alphabetic patch files (patch-A.MPQ to patch-Z.MPQ in order)

As we can see, the important difference between english and some common non-english localizations is that in english clients, **base** archives have the highest priority, while for non-english localization, **locale** archives have the highest priority.

#### Folder MPQs

If a [special binary flag](https://model-changing.net/applications/core/interface/file/attachment.php?id=3307&__cf_chl_tk=EsWzBnhq4nfzx4X2ryW_8HoRj_b53qYI_NmfVn6XJJU-1684430425-0-gaNycGzNC6U) is enabled in the wow.exe client, it is possible to make the game load **folders** located inside the Data directory just as if they were MPQ files, which is an extremely useful feature for modders so that we don't have to constantly package our edited files into compressed archives.

Here, we can see a folder called `patch-4.MPQ`, and its contents will be read and integrated into the clients priority list just as if it had been a "real" archive.

<img src="https://i.imgur.com/Q4iAUSn.png">


#### MPQ File Contents

The various MPQ files contain slightly different contents, as the purpose of the locale MPQs is to contain localization-sensitive data, however this is generally compressed into more generic categories, and locale MPQs do not _only_ contain localization data. Similarly, there are a few exceptions to exactly what kinds of files are stored where.

- Root MPQs
    - [M2/skin (Small 3D Models)](./m2)
    - [WMO (Large 3D Models)](./wmo)
    - [ADT/WDT/WDL (Map Data)](./adt)
    - [BLP (Texture data)](./blp)
    - [MP3](https://en.wikipedia.org/wiki/MP3)/[OGG](https://en.wikipedia.org/wiki/Ogg)/[WAV](https://en.wikipedia.org/wiki/WAV) (Sound/Music data)

- Locale MPQs
    - [DBC (Client Databases)](./dbc)
    - [Lua/XML (Interface)](./interface)

There is no rule that says what category of MPQ files must contain what files, and the client will happily read any file from whatever archive is highest in its internal priority list*. Because of the differences in this priority between english and non-english clients, they usually place their custom patches in different places:

- **English** clients usually place custom patches in the **root** data directory, since those patches will override all other archives.

- **Chinese/Russian/Non-english(?)** clients usually place custom patches in the **locale** directory, since those patches will override all other archives.


_* The only exception to this is a few files in the `shader` directory, which **must** be read from the base mpq files they were originally placed in._