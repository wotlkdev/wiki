---
layout: default
title: Server Databases
nav_order: 2
---

# Server Databases

WoW servers use MySQL databases to store both static and dynamic game data.

**Static** game data consists of things that define the game world itself, like _creatures_, _items_, _game objects_ and _quests_, and are things that do not normally change while the server is running

**Dynamic** game data consists of things that do change while the server is running, like _account data_, players _characters_, _creature respawns_ and _instance data and locks_.

Traditionally, MaNGOS-derived emulators use **three** databases to represent the static and dynamic game data that makes up the game world

## Auth Database

This is the first **dynamic** database and contains account data, security settings and realmlist data.

Despite its name, the auth database is used both by the authserver and worldservers, and its purpose is to contain all kinds of data **shared by multiple worldservers and authservers**, like players login information.

## Characters Database

This is the second **dynamic** database and contains character data, instance lockouts, creature respawns and other data that is used by **a single worldserver**.

Despite its name, it does not only contain character data, and the purpose of this database is to contain all kinds of data used by **a single worldserver**.

## World Database

This is the database used for **static data**, and can be both shared by multiple worldservers or used by a single worldserver depending on different projects needs.

## Example

Below is an example layout of three worldservers, all with their own private character database, and all sharing the same Auth database. Worldserver A and B share the same world database while worldserver C has its own private world database, maybe because it implements some kind of custom features that the other worldservers don't.

<img src="https://i.imgur.com/Snryg36.png">

## Source World Database

A special database that is only used by [TSWoW](https://tswow.github.io/tswow-wiki/) as a reference world database for use in _datascripts_. This database is never read by the core itself, and contains the same kinds of data as the normal world database.

## Relationships with DBC files

Server databases often have relationships with the clients [DBC files](./dbc), where server tables commonly point at fields in those files.