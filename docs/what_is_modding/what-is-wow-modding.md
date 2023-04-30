---
layout: default
title: What is WoW Modding?
---

# What is WoW Modding?

WoW Modding is a very broad practice, and it's easy to feel overwhelmed with the amount of options, tutorials, tools and possibilities that they present.

The aim of this article is to briefly describe the traditional "mod categories" that modders often choose to specialize in. Some modders learn how to do most or even all of these, while others specialize in only a few of them. These include:

- **Texture Editing**: Drawing or editing textures for the game.

- **Retroporting**: Porting content from the modern game to older versions.

- **Model Editing**: Creating and editing 3D models

- **Map Editing**: Creating and editing the game world and terrain.

- **Server Programming**: Reprogramming and scripting open source private server software.

- **AddOns**: Writing the same kind of AddOns used in the normal game to create client interfaces for custom projects.

- **Data Editing**: Editing the "data tables" that makes up much of the entities in the game, like spells and creatures.

- **Reverse Engineering**: Editing the client exe itself, or documenting the games binary file formats.

## Texture Editing

[[Insert Image of Texture Editing Here]]

Texture editing is a mostly creative task involving extracting textures from the game and editing/re-drawing them in your favorite image editor, or creating entirely new textures to use in the game.

Texture editing is mostly a creative practice, and requires very little technical expertise to do successfully.

## Retroporting

Retroporting is a type of mod that takes content from a more modern versions of the game and "backports" it to earlier versions. Retroporting is not limited to a particular type of mod or version of the game, and can include retroporting maps, 3D models, AddOns/Interfaces or gameplay features such as transmogging or pet battles.

In practice, many retroporters focus on 3D models or maps, and mostly target the Wrath of the Lich King version of the game.

### Skillset

Today, there are many graphical tools to help retroporting models and maps, and it's sometimes possible even for beginners to retroport some models. However, wow formats come with **a lot** of caveats and edge cases that often break the gui tools we have, so some technical proficiency is often necessary to learn how to deal with them.

Beginner retroporters often show proficiency in:

- Knowledge of what client formats exist in the game
- Basic knowledge of WoTLK 3D model formats.
- Editing binary files with ready-made templates
- Problem-solving, because things can easily go wrong.

Expert retroporters often show proficiency in:

- Deep knowledge of wows binary file formats across the different versions of the game
- Hex editing and hex editor scripting ("010 editor")

## Model Editing

Model editing involves creating or modifying the 3D file formats in the game. Most model editors for the game are written as **Blender** AddOns, and this is by far the most common model editor used for the game.

Model editing is itself often split into the following categories:

- Static Models (M2): Smaller game objects, props, items **(Easy)**
- Map Objects (WMO): Houses, caves, capitals **(Medium-Hard)**
- Animated Models (M2): Creatures, Player models, spells, boats. **(Hard)**

Static models and map objects have relatively mature workflows, while animated models is still highly experimental and often requires expert knowledge or very specialized tools to do successfully.

Model editors often show proficiency in:
- 3D modeling in Blender
- Knowledge of the basic 3D model formats used by the game, their features and limitations.
- Problem solving, because things can easily go wrong.

## Map Editing

The overworld map in World of Warcraft consists of something called a "heightmap", which is a two-dimensional grid that makes up the "terrain" of the world. This is the ground, hills, mountains and roads that you can walk on in the game. This "map" is distinct from other 3D models in the game, like houses, caves and capitals.

Map editing is commonly categorized into three parts:

- Sculpting, which involves creating the shape of the game map
- Texturing, which involves painting textures on the sculpted heightmap.
- Prop placement, which involves placing out 3D models like houses, trees, bushes, fences and so on into the world.

Map editors often work with the open source map editor "Noggit" to manually sculpt and paint the game terrain and place map models. Advanced map editors have also figured out different methods to automatically import sculpting and texture data from other sources, such as World Machine or Gaea.

Map editors often show proficiencies in:
- Level design
- Using the "Noggit" map editor
- Sculpting and painting
- Model editing, as many parts of the games map consists purely of 3D models, such as buildings, caves and capitals.
- Problem solving for more advanced uses, because things can easily go wrong with them.

## Server Programming

WoW is an online game that requires a server to function at all. Because of how complicated WoW is, creating a server from scratch is a monumental task that virtually nobody bothers doing anymore. Instead, we use one of the available open source servers as a basis to further customize our game by changing their existing programming for our needs. This server "base" is often referred to as the server **emulator** or **core**.

Server programming commonly comes in two basic categories:

- **Scripting**, which involves writing small extensions that reacts to events in the server core, often in a beginner-friendly language like **Lua** or **TypeScript**. Since scripting cannot modify all the internal workings of the server it comes with some limitations, but for many servers scripting is more than enough to achieve very customized results and with good enough performance for the vast majority of servers.

- **Core Editing**, which involves changing the **internal programming** of the server to fix bugs or to change how the game works at a fundamental level. This is done more or less exclusively with **C++**, and is significantly less beginner-friendly than scripting. Core editing is often used for the types of edits that scripts are not flexible enough to do, to fix internal bugs or for systems that are called very often and require very high performance.

## Client Interface / AddOn Development

Some custom wow projects use AddOns to create custom graphical interfaces for the game, much like how addons are developed for the 'normal' game. AddOns in World of Warcraft are written in `XML` and `Lua`, but some projects also enable writing them in `TypeScript`.

In custom wow projects, AddOn development often has a lot of overlap with serverside scripting and commonly involves using AddOn messages to communicate between the client and the server.

One of the difficulties of client interface development in WoTLK is poor documentation, and often requires learning how to read the code of existing AddOns to figure out how to do various things.

## Data Editing

Many of the "things" that exist in the game, such as spells, creatures, quests, items and so on are not created through raw programming, but are specified in rows and columns in special "data tables" (think 'excel sheets' or 'SQL tables') with predefined meanings that are read by both the client and server.

There are hundreds upon hundreds of these data tables used by the game and emulators, some of them with tens or hundreds of thousands of entries. For example, all spells in the game are specified in a special file in the client called `Spells.dbc`, which is just a large table with a bunch of columns that specify what each spell in the game does. Similarly, all the types of creatures in the game are specified in a similar serverside table called `creature_template`.

Data editing has a lot of overlap with server programming, and effects created in data tables are commonly listened to by server scripts to create highly specialized effects, especially for creatures and spells.

Becoming proficient with data editing involves learning the meanings of these tables, how they relate to each others and how to use them to get the game to do what you want. Some data tables in the game are very simple to edit, while others consists of hundreds of columns and cross-references to other tables that requires specialized software to edit effectively at all.

## Reverse Engineering

Reverse engineering refers to figuring out how an obfuscated system in the game 'works' to allow us to understand, replicate or modify it for our purposes. Almost everything we are able to mod in the game today is based on people in the past reverse engineering the games binary file formats and network protocol.

Today, a very large portion of these files and protocols is already documented for WoTLK, and thus we no longer need to 'reverse engineer' them. Instead, reverse engineers have shifted their focus to the client binary (wow.exe) itself and how to modify its internal code. The purposes for doing this varies, from fixing annoying bugs and driver issues to unlocking custom behavior otherwise impossible.

Reverse engineering is one of the most technically difficult aspects of wow modding, and requires a good understanding of how computer code and memory works, as well as reading x86 assembly code and using disassemblers like IDA or Ghidra.