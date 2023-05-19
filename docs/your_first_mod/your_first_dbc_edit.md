---
layout: default
title: Your First DBC Edit
nav_order: 4
---

# Your First: DBC Edit

For this tutorial, we will be using the [WDBX editor](https://github.com/WowDevTools/WDBXEditor) to make a very simple DBC edit that just changes the name of the **Fireball** spell.

## Grabbing our DBC files

To edit DBC files, we need to extract it from the clients MPQ archives and place it inside our custom patch under the directory `DBFilesClient`. You have two options for extracting DBC files:

1. By opening your clients **locale** MPQs with the MPQ editor and extract files from the `DBFilesClient` subdirectory

2. Copy already extracted DBCs from your servers **dbc** directory.

These files should be identical, so whichever method you choose doesn't matter. For this tutorial, we are looking for the file **Spell.dbc**. We want to move this file into our client patch directory befor editing it, such that the file `patch-4.MPQ/DBFilesClient/Spell.dbc` exists (or any other patch number/letter we chose for our custom patch).

<img class="mi ili80" src="https://i.imgur.com/AG22glt.png">

## Setting up WDBX

Download the latest WDBX Editor from the [GitHub Repository](https://github.com/WowDevTools/WDBXEditor/releases/latest), the file you want is the zip file `WDBX.Editor.zip`. Extract this file somewhere on your computer and start the program. You will be faced with the following screen:

<img class="mi ili80" src="https://i.imgur.com/FN7Q05Q.png">

Let's open our DBC file by navigating to `File -> Open Files`, then selecting our `Spell.dbc`

<img class="mi ili80" src="https://i.imgur.com/1gR1FEz.png">

WDBX will now ask us to select what version of the game this DBC belongs to, and we'll just select `WoTLK` here of course.

<img class="mi ili80" src="https://i.imgur.com/03YeRI9.png">

It will take the program a few seconds to open this file, as Spell.dbc is a very big DBC file. Once finished, we should have a screen like this:

<img class="mi ili80" src="https://i.imgur.com/fQgcOqn.png">

If you try to scroll around a little, you'll see that this is indeed a massive file. How do we navigate around it?

I will reveal for this tutorial that the spell id we are looking for is `133`, and there are two methods we can use to locate this row in the file:

### Go To ID

WDBX allows us to directly go to a row just by typing in its ID. We do this with the keyboard shortcut `CTRL + g`, which brings up a small box that allows us to type in the ID we want to go to:

<img class="mi ili80" src="https://i.imgur.com/W98xTES.png">

### String Search

If we don't know the ID of the row we want to go to, an alternative is to `search` for it, which we can do by pressing the keyboard shortcut `CTRL + f`, which will bring up a small box like this:

<img class="mi ili80" src="https://i.imgur.com/3wquWAl.png">

However, a word of warning, in WoTLK spells of different ranks all have the same name and there are very often dummy spells with the same names as other spells, so it's very easy to get the wrong spell if we just search for its name.

### Finding the "name" column

The Spell table has a lot of different columns that takes some time to learn how to navigate, but since we're looking for something like a name we can just scroll until we find it.

<img class="mi ili80" src="https://i.imgur.com/tCaK79L.png">

Now, changing the name of our spell is as easy as clicking the cell just like before and typing in something else.

<img class="mi ili80" src="https://i.imgur.com/xzL3kmo.png">

### Saving

To save the DBC, we can simply press the keyboard shortcut `CTRL + s`, or navigate to the `File -> Save` menu in the top bar.

<img class="mi ili80" src="https://i.imgur.com/9rELEvt.png">

With this done, we can restart our client, and if we create a new mage we should see that our fireball spell has the new name we gave it in the editor.

<img class="mi ili80" src="https://i.imgur.com/6P49xwv.png">

### Updating Server DBC Tables

For purely cosmetic things like Spell names, it's enough to just save our dbc file in the client patch and restart the client. However, many columns in the client DBCs are actually handled in the server, and we change things like numeric of damage values, it's important to remember to **copy** our edited DBC files back into the servers `dbc` directory.