---
layout: default
title: Your First SQL Edit
nav_order: 5
---

# Your First: SQL Edit

For this tutorial, we will be using the [HeidiSQL](https://www.heidisql.com/) editor to make a very simple SQL edit that just changes the name of **Hogger**.

## Starting HeidiSQL

Download [HeidiSQL](https://www.heidisql.com/installers/HeidiSQL_12.4.0.6659_Setup.exe) and start the program. You should be met by a screen like this:

<img class="mi ili80" src="https://i.imgur.com/GHJxW9X.png">

To connect to our server, we need to figure out the settings highlighted in the above screenshot, our `username`, `password` and `port`. Exactly what these are and where we can find them vary slightly between projects.

### Default Values

If you don't want to go looking for them, here are the default values for some popular emulators as of the time of writing this tutorial:

- <img width="32px" src="https://cdn.discordapp.com/icons/376073286427344897/d5538e2eea07f10103b6546eaeba76a7.png?size=240"> **TrinityCore**
    - **username**: trinity
    - **password**: trinity
    - **port**: 3306
    - **database**: world

- <img width="32px" style="border-radius: 50%;" src="https://cdn.discordapp.com/icons/217589275766685707/997a566468859317e9e22e9e782fb587.png?size=240"> **AzerothCore**
    - **username**: acore
    - **password**: acore
    - **port**: 3306
    - **database**: world

### Where to find these values

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

## Connecting

Once we have found the credentials we need, we can press the `Open` button at the bottom of this screen:

<img class="mi ili80" src="https://i.imgur.com/GKdSmX7.png">

If all went well, we should be met by a screen similar to this:

<img class="mi ili80" src="https://i.imgur.com/yj5vM5A.png">

The section to the left will list the current database we have open, and if we expand it we will see all the tables that are contained in that database.

## Customizing an existing creature name

So, how do we get started trying to edit the field we want for this purpose? There's tons of tables here!

Finding the initial table you're looking for can be tricky, and usually requires reading through a few (or a lot) of them before you find the one you want. This is something where asking for help is often a good idea.

For the sake of this tutorial, I'll reveal that you're looking for the `creature_template` table.

<img class="mi ili80" src="https://i.imgur.com/CIYWacT.png">

If we look at the column names, we should be able to see the `name` field pretty early, and looking at the entries in this table it seems to be the field we are looking for.

So, how do we find Hogger in all of these rows? Let's use HeidiSQLs "Filter" feature to find our row:

<img class="mi ili80" src="https://i.imgur.com/zAoHGea.png">

This little window allows us to write in a partial **SQL query** to filter the rows in the visible window. Teaching SQL syntax is beyond the scope of this tutorial, but a basic filter statement would be the query `name = "Hogger"`, which will select all rows where the "name" row contains the value Hogger.

<img class="mi ili80" src="https://i.imgur.com/XU1gfgl.png">

If we typed our query correctly, we should end up with just a single row left in the table with the name "Hogger". Now that we've found him, changing his name is as easy as clicking on the "Name" cell that reads Hogger and type in a new name:

<img class="mi ili80" src="https://i.imgur.com/n7yQnE2.png">

## Restarting

For some serverside tables, like creature_template, it is possible to reload their value without restarting by typing in the command `.reload creature_template <creature_id>` either ingame or the server console, otherwise you need to restart the server for effects to take place. 

The command to restart Hogger is thus: `.reload creature_template 448`

Before we go and visit the new Hogger, we need to make sure that we have cleared out our clients cache and restarted. The client cache is a folder inside the client folder that is used to temporarily save data that the client receives from the server about things like creatures. If we don't remove this folder, there is a chance that we will not see the new name when we log into the game, becasue the client had already cached the previous name.

**Always delete your cache directory when modding serverside tables**

<img class="mi ili80" src="https://i.imgur.com/yIOScHv.png">

If we log into the game go and visit Hogger now, he should instead have the new name we gave him:

<img class="mi ili80" src="https://i.imgur.com/HaWPTyA.png">