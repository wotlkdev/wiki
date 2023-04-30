# Your First: Data Edits

_Disclaimer: This article is written by one of the authors of TSWoW._

Data editing refers to adding or changing entries in the clients and servers data tables. This is used for modifying or creating things like:

- Items
- Spells
- Professions
- Classes
- Races
- And much more

## Prerequisites

To follow this tutorial, you should have completed the following tutorials (or have an equivalent setup ready):

- [[Your First Client Edit]]
- [[Your First Server]] (alternatively, [[Choosing a Core]])

## Data Tables

There are two types of data tables that we can edit in the game, **DBC** files and **SQL** tables.

* **DBC files** are binary files that come from the clients MPQ archives, but are used by both the client and server for custom projects.

* **SQL tables** are tables hosted in an SQL database and are only used by the server.

Some entities in the game are defined in DBC files, while others are defined in SQL tables. For example, **Spells** are defined in the DBC file `Spells.dbc`, while creature types are defined in the SQL table `creature_templates`

[[Images showing a dbc file and an sql table]]

## Approaches

There are three common approaches to data editing, **Table editors**, **Designers** and **TSWoW**.

* **Table Editors** are programs that allow you to edit the raw data tables rows and columns. SQL tables and DBC files have separate editors to do this.
    * _Examples: [[WDBX]] (DBC), [[HeidiSQL]] (SQL)_

* **Designers** [[what to call these???]] are programs specifically written to make editing some types of tables easier, such as Spells or creatures. There aren't such hand-tailored tools available for all tables in the game, so these are commonly used together with _Table Editors_.
    * _Examples: Spell Editor, Keira3 [[more examples!!]]_

* **TSWoW** is a special [[server core]] that uses a completely different approach to data editing by using a special scripting language instead of editors. TSWoW has first-class support for far more types of entities than most _Designer_ tools do today, but relies on navigating a simple scripting language and can generally not be used together with other data editing tools.

This tutorial will focus on using **Table Editors**, but may still be useful for Designer users who wants to understand how these tables work behind the scenes. 

_For TSWoW users: making these kinds of edits are not really possible in the same way for you, so you can safely skip this one. You can still read this tutorial if you want to understand how these tables work, but you should not try to make any of these changes yourself._

## Your First: SQL Edit

For this tutorial, we will be using the [HeidiSQL](https://www.heidisql.com/) editor to make a very simple SQL edit that just changes the name of **Hogger**.

It is assumed that you have [[installed a server core]] already and know how to start, stop and restart it.

### Starting HeidiSQL

Download [HeidiSQL](https://www.heidisql.com/installers/HeidiSQL_12.4.0.6659_Setup.exe) and start the program. You should be met by a screen like this:

[[Picture of HeidiSQL startup screen]]

To connect to our server, we need to figure out the settings highlighted in the above screenshot, our `username`, `password` and `port`. Exactly what these are and where we can find them vary slightly between projects.

#### Default Values

If you don't want to go looking for them, here are the default values for some popular emulators as of the time of writing this tutorial:

- **TrinityCore**
    - **username**: trinity
    - **password**: trinity
    - **port**: 3306
    - **database**: world

- **AzerothCore**
    - **username**: [[????]]
    - **password**: [[????]]
    - **port**: 3306
    - **database**: world

#### Where to find these values

For most cores, these fields can be found in your `worldserver.conf` file in your servers installation directory.

The field you are looking for is the one called `WorldDatabaseInfo`, which should be assigned to a string seprated by semicolons with the following format:

```
WorldDatabaseInfo     = "127.0.0.1;aaaaa;bbbbb;ccccc;ddddd"
```

where

- *aaaaaa* - is the **port** we need. This should be a number
- *bbbbbb* - is the **username** we need.
- *ccccccc* - is the **password** we need.
- *dddddd* - is the **database** we need.

### Connecting

Once we have found the credentials we need, we can press the `Open` button at the bottom of this screen:

[[filled out heidisql connection with "Open" highlighted]]

If all went well, we should be met by a screen similar to this:

[[heidisql full window view with trinitycore tables, with database list highlighted]]

The highlighted section to the left will list the current database we have open, and if we expand it all the tables that are contained in this database.

### Customizing an existing creature name

So, how do we get started trying to edit the field we want for this purpose? There's tons of tables here!

Finding the initial table you're looking for can be tricky, and usually requires reading through a few (or a lot) of them before you find the one you want. This is something where asking for help is often a good idea.

For the sake of this tutorial, I'll reveal that you're looking for the `creature_template` table. Let's open it up.

[[Picture of the creature_template table]]

If we look at the column names, we should be able to see the `name` field pretty early, and looking at the entries in this table it seems to be the field we are looking for.

So, how do we find Hogger in all of these rows? Let's use HeidiSQLs "Filter" feature to find our row:

[[picture of heidisql filter button and open editor]]

This little window allows us to write in a partial **SQL query** to filter the rows in the visible window. Teaching SQL syntax is beyond the scope of this tutorial, but a basic filter statement would be the query `name = "Hogger"`, which will select all rows where the "name" row contains the value Hogger.

[[picture of this filter with the "Apply Filter" button highligted and showing only hogger]]

If we typed our query correctly, we should end up with just a single row left in the table with the name "Hogger". Now that we've found him, changing his name is as easy as clicking on the "Name" cell that reads Hogger and type in a new name:

[[picture showing us selecting that field and typing in something else]]

### Restarting

For some serverside tables, like creature_template, it is possible to reload their value without restarting by typing in the command `.reload creature_template <creature_id>` either ingame or the server console, otherwise you need to restart the server for effects to take place. 

The command to restart Hogger is thus: `.reload creature_template 448`

If we go and visit Hogger now, he should instead have the new name we gave him:

[[picture showing us by Hogger]]

### If the above didn't work

There is a chance that the above did not work for you. This might be because your client had already cached the old name for Hogger, and doesn't receive the new one.

This is perhaps one of the most important lessons of this tutorial: **Always clear out your client cache when you change something in your server tables**. You can do this simply by deleting the folder called `Cache` in your client directory and restart the client.

[[picture of deleting the Cache folder]]

## Your First: DBC Edit

For this tutorial, we will be using the [WDBX editor](https://github.com/WowDevTools/WDBXEditor) to make a very simple DBC edit that just changes the name of the **Fireball** spell.

It is assumed that you have [[installed a server core]] already and know how to start, stop and restart it, as well as set up a [[client patch folder]].

### Grabbing our DBC files

To edit DBC files, we need to extract it from the clients MPQ archives and place it inside our custom patch under the directory `DBFilesClient`. You have two options for extracting DBC files:

1. By opening your clients **locale** MPQs with the MPQ editor and extract files from the `DBFilesClient` subdirectory

2. Copy already extracted DBCs from your servers **dbc** directory.

These files should be identical, so whichever method you choose doesn't matter. For this tutorial, we are looking for the file **Spell.dbc**. We want to move this file into our client patch directory befor editing it, such that the file `patch-4.MPQ/DBFilesClient/Spell.dbc` exists (or any other patch number/letter we chose for our custom patch).

[[picture of Spell.dbc in this patch dir]]

### Setting up WDBX

Download the latest WDBX Editor from the [GitHub Repository](https://github.com/WowDevTools/WDBXEditor/releases/latest), the file you want is the zip file `WDBX.Editor.zip`. Extract this file somewhere on your computer and start the program. You will be faced with the following screen:

[[picture of wdbx with nothing open]]

Let's open our DBC file by navigating to `File -> Open Files`, then selecting our `Spell.dbc`

[[picture of wdbx with those things selected]]

[[picture of file dialog with this file selected]]

WDBX will now ask us to select what version of the game this DBC belongs to, and we'll just select `WoTLK` here of course.

[[picture of this dialog]]

It will take the program a few seconds to open this file, as Spell.dbc is a very big DBC file. Once finished, we should have a screen like this:

[[picture of Spell.dbc opened]]

If you try to scroll around a little, you'll see that this is indeed a massive file. How do we navigate around it?

I will reveal for this tutorial that the spell id we are looking for is `133`, and there are two methods we can use to locate this row in the file:

#### Go To ID

WDBX allows us to directly go to a row just by typing in its ID. We do this with the keyboard shortcut `CTRL + g`, which brings up a small box that allows us to type in the ID we want to go to:

[[picture of this box]]

#### String Search

If we don't know the ID of the row we want to go to, an alternative is to `search` for it, which we can do by pressing the keyboard shortcut `CTRL + f`, which will bring up a small box like this:

[[picture of this box]]

However, a word of warning, in WoTLK spells of different ranks all have the same name and there are very often dummy spells with the same names as other spells, so it's very easy to get the wrong spell if we just search for its name.

#### Finding the "name" column

The Spell table has a lot of different columns that takes some time to learn how to navigate, but since we're looking for something like a name we can just scroll until we find it:

[[picture of this column]]

Now, changing the name of our spell is as easy as clicking the cell just like before and typing in something else.

#### Saving

To save the DBC, we can simply press the keyboard shortcut `CTRL + s`, or navigate to the `File -> Save` menu in the top bar.

With this done, we can restart our client, and if we create a new mage we should see that our fireball spell has the new name we gave it in the editor.

[[screenshot of wow client showing new spell name]]

#### Updating Server Tables

For purely cosmetic things like Spell names, it's enough to just save our dbc file in the client patch and restart the client. However, many columns in the client DBCs are actually handled in the server, and we change things like numeric of damage values, it's important to remember to **copy** our edited DBC files back into the servers `dbc` directory.

[[showing copying a file from our patch directory to servers dbc directory]]

#### Find and Replace

**Removed section, the Find and Replace feature is completely broken currently.**

~~If we level up our mage we will quickly find that newer ranks of the Fireball spell still have the old name. This is because spell ranks are entirely separate rows with their own unique spell ids.~~

~~_Before attempting this step, make sure to close your wow client first._~~

~~If we want to change multiple rows at once, we can use the `Find and Replace` command, which we can get by pressing the `ctrl + h` shortcut inside of WDBX, bringing up this box:~~

~~[[picture of the replace window with nothing added to it]]~~

~~Here, we can now type in the name `Fireball` and what we want to replace it with, then press "Replace all".~~

## Learning more

The edits we've made so far have been mostly trivial just to get you started with using the editor tools.

To learn more about what all these columns mean and what they do, there are a few resources available.

### SQL Tables

Documentation is generally dependent on your core version, as these tables differ slightly between them:

- [TrinityCore](https://trinitycore.atlassian.net/wiki/spaces/tc/pages/2130013/World)

- [AzerothCore](https://www.azerothcore.org/wiki/database-world)

- TSWoW: datascript code comments and the standard library, but for raw editing mostly identical to [TrinityCore](https://trinitycore.atlassian.net/wiki/spaces/tc/pages/2130013/World).

### DBC Files

todo

## Summary

In this tutorial we have learnt:

- How to use the **HeidiSQL** editor to edit serverside SQL tables
- How to change creatures names
- How to use the **WDBX** editor to edit DBC files
- How to change spell names

This is just a small dip into what we can possibly edit in these tables. To learn more about what all these different tables and columns do, there are a 