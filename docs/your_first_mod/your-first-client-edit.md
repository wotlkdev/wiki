---
layout: default
title: Your First Client Edit
---

# Your First: Client Edit

This tutorial will guide you to creating a very simple replacement of the login screen background music. This might not be a very interesting mod for most people, but the purpose is to have a barebones example to illustrate the following important concepts:

- How client asset files work
- What MPQ files are, how to read them and how they work
- How to create your own archive folder that the game will read files from.

If you already have a good grasp of how MPQ files and folders work you can comfortably skip this tutorial.

## Client Data Files

All data files in the WoTLK client is stored in the `Data` directory.

[[Image of the data directory]]

This directory contains files called "MPQ" files. MPQ is a type of archive similar to zip files that contain all the assets that the game uses, from 3D models, textures, audio files, map files, data tables, user interfaces and so on.

Inside the `Data` directory is also another directory with a name depending on the locale of your game, for example `enUS` for american clients, `enGB` for british clients, `ruRU` for russian clients and so on. This directory contains some additional `.MPQ` files that are usually more focused on things that need translation, such as data tables and client interfaces.

[[Image of the locale directory]]

## MPQ Archives

As explained above, MPQ is a type of 'archive' file that contains many other files within them in a directory hierarchy, just like a zip file. 

### Reading an MPQ Archive

Reading and writing MPQ archives requires a special program called [MPQ Editor](http://www.zezula.net/download/mpqeditor_en.zip). This is a program that works similar to zip archivers like 7-zip or WinRAR, but also supports some more advanced features that the MPQ format offers.

Let's try opening an MPQ archive to see what it contains. Download MPQEditor from the link above and start the program `MPQEditor.exe`.

You should be met with a window that looks like this:

[[Screenshot of MPQEditor]]

To open an MPQ archive, we navigate to the `MPQs` button to the top-left and click `Open MPQs`.

[[Picture of what to click to get there]]

A file dialog will open and allow us to select what archive we want to open. Let's navigate to our WoW client directory and open `common.MPQ`.

Once the file has opened, we should be met with a list of directories. These are the internal files contained in this archive.

### File Overriding

MPQ archives are not just mere zip archives, but include some powerful features that are very useful for modders.

The most important of these is the ability for the game client to load multiple MPQ archives at the same time and "override" files from one archive with files from another.

For example, let's say that we have the two mpq archives `patch-1.MPQ` and `patch-2.MPQ`.

[[Picture of patch-1.MPQ and patch-2.MPQ]]

Let's also say that both archives inside them contains a file called `my-song.mp3`.

[[Picture of two MPQ editors with that file]]

When the client starts, it will open both these archives, but when it looks for a file called `my-song.mp3`, it will notice that this file is present in both `patch-1.MPQ` and `patch-2.MPQ`. Then, it will decide that because `patch-2.MPQ` has a higher number in its name, it will **only** read the file from this archive, and ignore the one in `patch-1.MPQ`.

[[Diagram showing this]]

If we were to remove the file from `patch-2.MPQ` and restart the game, it would instead fall back to the file in `patch-1.MPQ` instead.

[[Diagram with the file removed from patch-2.MPQ]]

This feature of MPQ archives allows modders to modify any file in the client without ever touching the existing MPQ files, since we can always just override any files by creating additional patch archives. Considering how many files the base game contains, this is a godsend for project structure.

[[Diagram adds a patch-A.MPQ and mark it as a "modders patch"]]

### Reading Multiple MPQ Archives

MPQEditor is able to read multiple MPQ archives just like the client does and automatically override files when it does so.

Let's try opening all the MPQ archives in the `Data` directory at the same time. First, we close the current MPQ archive under the `MPQ` button to the top left and selecting `Close MPQ`

[[Screenshot]]

Then, we'll select `Open MPQ` again just like when we opened the first file, but this time we'll select all the MPQ files in the file dialog before we hit "Open"

[[Screenshot of file dialog]]

Because we chose to open multiple MPQ archives, the program presents us with an additional dialog asking us how we want those files opened. The only thing we need to do here is make sure that `Merged mode` is selected before we hit okay. This ensures that MPQEditor tries to read the files the way the client would.

[[Screenshot of dialog with red markings on "Merged mode" and "Ok"]]

Once we finished opening all the MPQ archives, we are presented with a similar list of directories as in the first step. The difference is that this represents the sum of all the opened MPQ arhives, with individual files in higher patches automatically overriding those in lower patches.

### Extracting Files

Our end-goal in this guide is to replace the login screen music of the game, so let's navigate to the folder that contains this music and take a look. These files are located in the directory `Sound/Music/GlueScreenMusic`. This directory should contain four mp3 files if we opened all archives correctly.

[[Screenshot of navigating these directories]]

This directory should contain four files if we opened all archives correctly.

[[Screenshot]]

The easiest way to extract these files is to just select them in MPQ editor and "drag them" over to a folder open on our computer. As we do this, the program will blink a bunch before it lets us drop the files, but we should then be able to drop them off without issue.

[[Screenshot]]

The names of these songs seem to be relatively self-explanatory. If we listen to the file `WotLK_main_title.mp3` we'll hear the wotlk login screen music, for `BC_main_theme.mp3` we'll hear the tbc music, and for `wow_main_theme.mp3` we'll hear the vanilla music.

## Creating our own patch

_Note for TSWoW users: Your process for doing this is going to be slightly different in practice, but I still recommend that you try doing this manually once to get an idea of patches work under the hood._ 

Messing around with MPQ archives can be annoying, since we need a special editor just to open them. For this reason, many modders have discovered another feature of the wow client that can be enabled by rewriting some of its internal code.

This edit makes it possible for the game not only to load files from MPQ archives, but from plain **folders** that just have the same name as an MPQ archive, such as a folder in the `Data` directory called `patch-4.MPQ`. For the client, these folders are treated just as if they were an actual MPQ archive, and is taken into the same consideration for file overriding.

You can download a ready-patched client exe from [mediafire](https://www.mediafire.com/file/kewam47gtdshhln/Wow.exe/file) or [model-changing](https://model-changing.net/applications/core/interface/file/attachment.php?id=3307), or you can follow the manual steps in [this guide](https://model-changing.net/index.php?app=tutorials&module=tutorials&controller=view&id=24) if you want to apply the patch to the exe yourself.

[[Screenshot of downloaded wow.exe]]

With the patched exe installed, we can create our own patch for the game inside the `Data` folder called `patch-4.MPQ`. Since all the builtin patches in the game have numbers below 4, this folder will override all of them.

[[Screenshot of this patch]]

Now, we have all the pieces needed to create our new login screen music.

If we remember from the previous section, we exported the file with the full path `Sound\Music\GlueScreenMusic\WotLK_main_theme.mp3`. To override this file, we'll simply need to place another mp3 with the same local path inside our newly created patch archive. Any mp3 should work for this, but if you don't have any laying around, you can use the `wow_main_theme.mp3` that we extracted earlier and just rename it. Please note that you cannot rename `.wav` or `.ogg` files without converting them to `.mp3` first.

[[Screenshot of the new directory]]

If we did all steps correctly we should now hear our own mp3 play when we restart the game.

## Summary

In this tutorial, we learnt:

- How the files in the clients `Data` directory work and what they contain.
- How to open individual and merged `MPQ` files.
- How to extract files from `MPQ` files.
- How to create our own patch directory to add and override files to the client.