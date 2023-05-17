---
layout: default
title: Emulation
nav_order: 10
---

# Emulation

[[Insert Image of core development Here]]

World of Warcraft is a very complicated game, and it has taken server developers decades of work to get to where they are today.

What a server core is actually doing is called _emulation_, meaning that it pretends to be a piece of machinery that it is not. In this case, wow private server emulators pretends to be an official blizzard wow server.  This is not all that unlike what video game console emulators do, like **snes9x** for the SNES or **Dolphin** for the Nintendo Wii, with the difference that WoW servers emulate _network packets_ instead of processor architectures and focuses on a _single game_ instead of an entire game console.

## Emulating World of Warcraft

When we talk about emulating the Blizzard Servers for World of Warcraft, we usually talk about things like:

- Sending the correct **network packets** to the client, and correctly interpret the ones that the client sends back.

- Having the game world contain the correct creatures in the right places and with the correct stats

- Having spells and scripted bosses behave correctly

### Network Packets

Figuring out the kind of network packets an emulated WoW server is supposed to send is done through a process called **sniffing**.

Sniffing is a form of [[Reverse Engineering]], where we connect a WoW client to the official Blizzard servers and intercept all network packets that it receives. Once we have collected such packets, we can _analyze_ them, and try to figure out how to make our own servers send the same kind of packets.

Sniffing often requires high technical proficiency, but luckily for us the **structure** of virtually all network packets used in WoTLK have already been mapped out for us, and are readily available in all the popular server cores. What can still be difficult to get right is knowing exactly what packets to send when, and how exactly to respond to packets sent by the client.

### Data and Stat Values

Figuring ut the correct data and stat values in the game can be done in various ways, from simply watching and writing down numbers from the live game to analyzing old youtube videos and sniffing even more network packets.

For a very long time, official woTLK servers were not available, so many emulators relied on old videos and data from previous private servers, but along with classic servers we can yet again collect this data by sniffing and analyzing official data.

### Scripting

Figuring out scripting is often a very manual process that try to figure out the most generalized ways to program the server to handle different types of spells and scripted boss encounters.

## Emulation and Modding

But, you might think, isn't this a guide to **modding** the game? Why should modders care about emulation?

For modders, emulating the game perfectly is of course not always the goal, but since the game is so complicated modders **almost always use the same server emulators** that blizzlike servers do.

To a beginner, this may seem like a drawback, and sometimes it is. For most core developers, emulation is the goal and modding a secondhand consideration, which can sometimes lead to design decisions that aren't the best for modders.

However, sharing cores like this between a vast array of projects also has some great benefits that beginners don't always realize:

- More centralized development means everyone shares the same stability fixes and performance enhancements

- Even modded servers often want large parts of the game intact, like Vanilla+ style projects.

- Good emulators often correctly interpret client database tables **without making assumptions about them**, meaning modders can **add** or **modify** things in them without having to write additional code to handle those modifications.