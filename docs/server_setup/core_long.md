---
layout: default
title: Choosing a Core (Long)
nav_order: 2
---

# Choosing A Core

_Disclaimer: This article is written by one of the authors of TSWoW._

_Note: If you only want to quickly set up a core to try out client modifications, see [[Your First Server]]._

For a fully custom project, one of the most important decisions you can make is what server software to use as a basis for your project.

A server **core**, or **emulator** (in wow, these terms mean more or less the same thing) is a program that acts as the game server that your client can connect to. Most cores for WoTLK are open source and can be downloaded by anyone for free.

## Source vs Repack

There are typically two ways to install a server core, either by building it directly from source code or by downloading an already compiled executable called a 'repack'.

- **Repacks** are generally slightly easier to set up and commonly support some limited scripting, but you cannot change their internal programming.

- **Building from source** is generally slightly harder to do, but allows you to fully modify the all parts of the server.

## Similarities and Differences

Server cores are typically always written in C++, and today almost all popular server cores all come from a single project called **MaNGOS**. This means very large parts of different cores look very similar to each others, but there are still important differences between them:

- How much of the 'Blizzlike' game is implemented
- Performance
- Licenses
- Builtin support for custom features

What core to use for your custom project depends what aspects of the game are most important for you. Virtually all cores support _some_ level of customization, and things like items, creatures, spells, skills and gameobjects are supported by all cores.

## Licenses

While most server cores are 'free' as in that they don't cost money, that doesn't mean you are allowed to use them however you want. If you use their code in your own projects, you must follow their **licenses**.

Luckily, most licenses are very permissive and mostly govern **when you have to publish your own modifications of the source code**. The most common licenses used are the GPL and the AGPL:

- **AGPL**
    - **Publish a repack**: Must publish all your source code
    - **Host a server**: Must publish all your source code

- **GPL**
    - **Publish a repack**: Must publish all your source code
    - **Host a server**: Don't need to publish any source code

## General Purpose Server Cores

What core to use is a highly debated topic, usually revolving around arguments about "performance", "stability", "helpful community" or "competent/incompetent developers".

While these aren't bad things to investigate for yourself, for this article we will focus on the things that are reasonably measurable and almost everyone agrees on.

For serious custom projects it is **highly advisable** to look into these matters further on your own.

###  <img width="64px" src="https://cdn.discordapp.com/icons/376073286427344897/d5538e2eea07f10103b6546eaeba76a7.png?size=240"> [TrinityCore](https://trinitycore.atlassian.net/wiki/spaces/tc/overview)

- **Started:** 2008
- **Based on:** MaNGOS
- **License:** GPL
- **Custom Projects using it:**
    - Project Ascension
    - Hour of Twilight
    - ShinobiStory
- **Scripting Languages:** C++, Lua (with Eluna)
- **Pros:**
    - Used by many large custom projects

TrinityCore is a tried and tested core with more active custom projects than any other core, but has less builtin support for custom features or ready-made custom modules compared to other cores.

### <img width="64px" style="border-radius: 50%;" src="https://cdn.discordapp.com/icons/217589275766685707/997a566468859317e9e22e9e782fb587.png?size=240"> [AzerothCore](https://www.azerothcore.org/)

- **Began:** 2016
- **Based on:** TrinityCore
- **License:** AGPL
- **Scripting Languages:** C++, Lua (with Eluna)

AzerothCore is a very actively developed core that focuses heavily on Blizzlike content, but also has a large amount of custom modules focused on serverside behavior, but has less extensively custom projects using it compared to other cores.

### <img width="64px" src="https://cdn.discordapp.com/icons/793065928870854667/455d9131fd64cc40a99937898a91d5a8.png?size=240">[TSWoW](https://tswow.github.io/tswow-wiki/) 

- **Began:** 2021
- **Based on:** TrinityCore
- **License:** GPL
- **Custom Projects using it:**
    - Project Epoch
- **Scripting Languages:** TypeScript, C++, Lua

TSWoW is very different from other projects and is more of a 'framework' for customizing the entire game than just a server. For this reason it supports more advanced custom features out of the box than any other core by far, but has poor support for editors like Keira and Spell Editor, and instead relies on its own powerful scripting languages to create and modify data.

## Summary

Most custom projects today use either TrinityCore, AzerothCore, or TSWoW.

- TrinityCore and AzerothCore are fairly similar in terms of project structure, but are two very different cores internally.
- TrinityCore and TSWoW use virtually the same internal core and share most updates, but have very different project structure for modders.
- All cores support _basic_ custom features like creatures, items, maps, game objects, spells, scripting and so on.