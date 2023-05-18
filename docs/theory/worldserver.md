---
layout: default
title: Worldserver
nav_order: 1
---

# Worldserver

This article will contain a surface-level explanation and introduction to how the worldserver works and how you can navigate its source code.

It is not meant to be an all-encompassing technical outline, as the worldserver is far too complex to even begin to explain in a single article. Being able to navigate complex source code is an important skill to be able to master the worldserver, but this document might help get beginners started to know where to start looking.

## Code References

The vast majority of this article should be applicable to any modern core as they are all very similar to each others, but is primarily based on TrinityCore.

Code references will point at a particular commit in TrinityCores git history to ensure it always points at the right function names. You can read these links to get a general idea of what different functions are doing, but you should not use it to figure out what your own server is doing, since their implementation may have changed since.

In rare circumstances, some of the functions listed in this article may be removed in newer versions of the server source code.

## Execution Overview

The worldserver executable has three (four) main phases: initialization, game loop, shutdown and crash handler. The execution flow of the primary phases are relatively straightforward, while the crash handler is a special procedure that is only called when something goes wrong.

<img src="https://i.imgur.com/M25FjTR.png">

### Initialization

<img src="https://i.imgur.com/cTpqE1c.png">