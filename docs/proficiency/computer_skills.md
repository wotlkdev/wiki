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