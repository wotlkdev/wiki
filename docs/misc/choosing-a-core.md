---
layout: default
title: Choosing a Core
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

In this list, we will avoid more contentious topics or platitudes like:

- Performance/Stability
- "Helpful community"
- "Competent/incompetent developers"

We will instead stick to the things almost everyone agrees on and illustrates how these projects actually differ. For serious custom projects it is advisable to look into these matters further on your own.

### [[TrinityCore]]

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

TrinityCore is a tried and tested core with more active custom projects than any other core, but has more barebones support and ready-made modules for custom features.

### [[AzerothCore]]

- **Began:** 2016
- **Based on:** TrinityCore
- **License:** AGPL
- **Scripting Languages:** C++, Lua (with Eluna)
- **Custom Projects using it:**
    - ???

AzerothCore is a very actively developed core that focuses heavily on Blizzlike content, has a very large amount of custom modules focused on serverside behavior, but has less extensively custom projects using it compared to other cores.

### [[TSWoW]]

- **Began:** 2021
- **Based on:** TrinityCore
- **License:** GPL
- **Custom Projects using it:**
    - Project Epoch
- **Scripting Languages:** TypeScript, C++, Lua

TSWoW is very different from other projects and is more of an entire framework for customizing the game, both the server and the client. For this reason it supports more advanced custom features out of the box than any other core by far, but is heavily oriented around scripting and has poor support for editors like Keira and Spell Editor.