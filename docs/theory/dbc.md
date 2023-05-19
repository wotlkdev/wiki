---
layout: default
title: DBC Files
nav_order: 15
---

# DBC Files

The locale MPQs contain special database files called "DBC" files. DBC files are some of the most important files in the game, and define almost every kind of "thing" that exists in the game world, and is where modders can go to define their own. There are a total of 246 DBC files in the game, including definitions for (among many many others): 

- Spells
- Items
- Maps
- Classes
- Class stat data
- Races
- Hair/Facial Hair/Face/Skin color settings
- Gems
- Enchantments
- Titles
- Achievements
- Worldmaps
- Talents
- Battlegrounds and Arenas
- Flight Masters and Paths
- Transport Paths (boats and zeppelins)
- Elevator Paths (undercity, thunderbluff, deeuprun tram train)
- Display metadata for items, creatures and game objects

All DBC files have the same basic tabular format with rows for entries and columns with meanings specific to the individual DBC file, very much like a binary representation of an SQL table (which is very likely how Blizzard actually created them).

A technical explanation for the DBC binary file format can be found on the [wowdev wiki](https://wowdev.wiki/DBC).

## Server Database Relationships

DBC files often have relationships with the [servers databases](./server_database), where fields in DBC files sometimes point at server tables, and (more often) fields in the server database pointing at fields in DBC files.

For example, things like creatures and items are halfway defined in serverside tables (names and basic stats) and halfway defined in DBC files (mainly display data).

There is no great general resource for all of these relationships and all the things that actually go into creating various entities in the game, but they are usually mentioned in the server database documentation, and specific guides for creating entities will commonly mention the tables involved.

[TSWoW](https://tswow.github.io/tswow-wiki/) handles many of these relationships in their _datascripts_ automatically, and often provide simplified interfaces for creating otherwise very complicated entities that normally require editing a large amount of DBC files.

## Editing DBC Files

DBC files can be edited by table editors like [WDBXEditor](https://github.com/WowDevTools/WDBXEditor) or modding frameworks like _TSWoW_, and a documentation of all the files and columns that exist in those files for 3.3.5 can be found in the [DBC](../dbc) section on this website.

_Example of editing DBC file with WDBXEditor_
<img src="https://i.imgur.com/8P38ecN.png">

_Example of generating DBC data with TSWoW_

```ts
import { std } from 'wow/wotlk';

std.Spells
    .create('mymod','myspell')
    .Name.enGB.set('My Spell')
    .Effects.addMod(x=>x
        .Type.SCHOOL_DAMAGE.set()
        .DamageBase.set(1007688)
    )

    .SkillLines.addMod(150,'DRUID',[],(sla)=>sla
        .AcquireMethod.LEARN_ON_CREATE.set()
    )
    .InlineScripts.OnCast((x)=>{
        if(x.GetCaster().ToPlayer())
        {
            x.GetCaster().ToPlayer()
                .SendBroadcastMessage(`Cast the spell!`)
        }
    })
```