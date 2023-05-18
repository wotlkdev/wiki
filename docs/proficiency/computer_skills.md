---
layout: default
title: Computer Skills
nav_order: 1
---

# Computer Skills

Being able to navigate a computer effectively is an important foundation for anything to do with modding. It is more or less unavoidable when modding that you will end up having to deal with things like:

- Complicated directory structures
- Text-based and binary file types
- Tools that don't work the way they should
- Tools with next to no documentation
- Having to guess what your edits are even doing.
- Command-line based programs

If you haven't done modding before or are new to using PCs for anything besides gaming or browsing the web, this might make your early time in WoW modding a little rough, as many tutorials and guides assume a basic understanding of PC concepts, and many modders growing up in a time where PC knowledge was more widespread than today.

However, just like you, more or less everyone who started out modding at one point just had to download a bunch of weird programs on their computers and click on random buttons until something happened. What's important to make it through those challenges is:

- Patience with yourself and the frustrations you'll encounter.
- Respect for your current understanding so you don't overwhelm yourself.
- Insistance to keep practicing and finding interesting challenges that teach you something new.

## What to learn and where to learn it

Some people prefer to try to learn computer skills by "bashing their heads on whatever they're trying to do", while others prefer courses or tutorials to get started.

The rest of this article will attempt to give a few pointers to what kind of skills you might want to learn and where you can go to learn them.

## Foundational Computer Knowledge

If you have barely opened a PC before and you're scared of things like **files** and **folders**, you might want to look into an introductory computer course offered by your local library or other association. 

There are also some online courses and tutorials available, but I haven't found any suitable to list here.

## Command-line Interfaces

Many tools in wow modding rely on typing in text into a command prompt, as opposed to GUIs with pictures and buttons. To effectively use command-line tools it is often useful to have a basic of how the builtin windows command-line works.

- [thenewboston](https://youtu.be/MBBWVgE0ewk?list=PL6gx4Cwl9DGDV6SnbINlVUd0o2xT4JbMu) has a very good introductory guide to the windows command-line, and the **whole playlist** is highly relevant for things you can encounter in wow modding.

- [ThioJoe](https://youtu.be/H0gwnFV_SFs) has a short video explaining the differences between the two command shells in Windows, `PowerShell `and `cmd`.

## Networking

Since WoW is an online game, knowing some basic networking is very useful to help set up your server to let others play on it.

_Warning: hosting any private servers publicly **can** get you into legal trouble. This guide is for educational purposes only._

### Port Forwarding

Port forwarding is a configuration on your home router to allow other people to connect to servers you host from your own computer. This can be useful for playing with a small group of friends, similar to how many people host Minecraft servers.

- [This video](https://youtu.be/WOZQppVNGvA) gives a short explanation of what port forwarding is and why it's necessary.

- [This video]() is a good general tutorial for port forwarding
    - The ports you want to forward for WoTLK servers is usually 8085 for the worldserver and 3724 for the authserver.

- [This video](https://youtu.be/Jduk9KqU844) gives a short example for how to port forward a WoW server, and includes some **important additional steps** that they need.
    - Sometimes, the username/password on your router will be different from the ones in the video.
    - This video is for cataclysm, but works the same for WoTLK.

### Remote Hosting

For larger wow private server projects, most people rent servers in a remote location instead of hosting from their own home computers. Learning how to set up and manage such remote servers is a skill on its own, and not something you should save for the last minute when developing a custom wow server.

- [Different Types of Web Hosting Explained](https://youtu.be/AXVZYzw8geg) discusses the different types of remote hosting that are commonly offered by these companies. It focuses on hosting websites, but most of what he says is also relevant for wow servers.

- [A Very Simple VPS Server Tutorial For Beginners](https://youtu.be/YiwBkRukugw) shows how to set up up a simple remote server from start to finish. While it's not relating to hosting WoW servers, it's very good for giving you an idea of how setting up a server like this looks like.

## Programming

One of the most useful skills you can learn to increase your modding skills is a programming language. 

Programming is **everywhere** in WoW modding, from server scripts and internal code to all the tools and custom workflows that can fit your own projects needs.

What programming language to learn depends greatly on your previous experience and what you want to be able to achieve with it. Below is a list of the common programming languages in WoW modding and how you can go about learning them.

### <img width="64px" src="https://upload.wikimedia.org/wikipedia/commons/c/cf/Lua-Logo.svg"> Lua

- One of the most popular scripting languages for private servers
- Used for server scripting with tools like [Eluna](https://github.com/ElunaLuaEngine/Eluna) and for client addon development.
- Is a relatively simple language to learn and highly suitable for beginners.
- _TODO: if you know a good tutorial about Lua for beginners, please make a pull request._

### <img width="64px" src="https://upload.wikimedia.org/wikipedia/commons/thumb/4/4c/Typescript_logo_2020.svg/1024px-Typescript_logo_2020.svg.png"> TypeScript

- The primary language used in the [TSWoW](https://tswow.github.io/tswow-wiki/) project, but can also be used in place of Lua in [AzerothCore](https://github.com/azerothcore/eluna-ts) to provide better code completion and type checking.

- Is a relatively simple language to learn, comparable to Lua and Python.

- TSWoW DataScript is an even simpler variant of TypeScript that barely requires any programming experience at all, and is used to procedurally create SQL and DBC data.

### <img width="64px" src="https://upload.wikimedia.org/wikipedia/commons/thumb/c/c3/Python-logo-notext.svg/800px-Python-logo-notext.svg.png"> Python

- Used in various wow modding tools, mostly for managing various client formats and in Blender plugins like WoW Blender Studio.
- There is currently no way to use python for server scripts currently.
- Is about as easy to learn as Lua, but the WoW modding codebases that use Python are relatively complex and rarely suitable for beginners.

### <img width="64px" src="https://upload.wikimedia.org/wikipedia/commons/thumb/1/18/ISO_C%2B%2B_Logo.svg/800px-ISO_C%2B%2B_Logo.svg.png"> C++

- Used to write all modern server cores and most modding tools as well.
- Is one of the harder languages to learn, but can still be learnt by complete beginners if they are willing to spend the time necessary to understand its quirks.

- Despite its difficulty, it has many great learning resources:
    - [LearnCpp](https://www.learncpp.com/) is the most popular resource for learning C++ from scratch.
    - [The Cherno](https://youtu.be/18c3MTX0PK0?list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb) is a youtube channel with byte-sized tutorials that explains various topics about the language in very simple ways aimed at beginners.
    - [Effective C++](https://www.amazon.com/Effective-Specific-Improve-Programs-Designs/dp/0321334876) and [Effective Modern C++](https://www.amazon.com/Effective-Modern-Specific-Ways-Improve/dp/1491903996) are two of the most highly regarded books once you're past the beginner stage. Reading these will give you a better understanding of the language than the vast majority of private server developers.

    - [C++ Concurrency in Action](https://www.amazon.com/C-Concurrency-Action-Practical-Multithreading/dp/1933988770) is another great book to understand multithreading, which is a central concept in the structure of private server core.