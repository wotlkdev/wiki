---
layout: default
title: Server Debugging (Windows) (Unfinished)
nav_order: 5
---

# Server Debugging (Windows) (Unfinished)

Debugging is a powerful method to figure out exactly what a running program is doing while it does it.

A _debugger_ is a type of program used to take control of another program in order to see what it is doing and what data is in its memory. In WoW development, the debugger we use is usually _Visual Studio_, and the executable we debug is usually the _worldserver_, but any program can be attached to a debugger.

WoW servers are written in C++, and for a debugger to be useful in practice it is generally necessary to have a basic understanding of C++. Beginners might still find some value in skimming over this section to get an idea of what core developers actually mean when they talk about "debugging the server".

## Compiling for Debugging

In order for our debugger to do anything useful, we need to compile the worldserver in **Debug** mode. This makes the server significantly slower and should never be used on a live production server.

### Repacks

If you are using a repack, you cannot recompile the program in debug mode. You need to build your core from source for that..

### TrinityCore/AzerothCore

Building in Debug mode is as easy as opening the project in Visual Studio and changing the build type, then recompile. Your new core folder should be built into the same base folder as your previous builds, but into `Debug` instead of `RelWithDebInfo` or `Release`. You can copy over your map/dbc/.conf/mysql/libcrypto files from the previous build.

### TSWoW

Building the core in debug mode can be done from the [interactive build prompt](https://tswow.github.io/tswow-wiki/installation/compiling) by typing in `build trinitycore-debug`.

Then, to make your tswow installation use the debug binary, change the `Default.BuildType` to `Debug` inside `tswow-install/node.conf`. Finally, if using C++ livescripts, make sure to rebuild them once from the main script (`build scripts`) and then start the server.

## Attaching the Debugger

First, we start our debug version of the worldserver the way you usually do for your core.

Then, we should open the Visual Studio project for the core.

Then, we navigate to the "Debug" menu window and select `Attach to Process`.

This should bring up a dialog like below, where we can search for `worldserver` to easily find our process, and then click "Attach" to attach the debugger.

## Breakpoints

TODO

I have not had time to write the rest of this tutorial yet, but this video explains some of the basics of how to actually use a debugger once you have attached it to some generic program:

<div align="center"><iframe width="420" height="315" src="https://youtube.com/embed/0ebzPwixrJA" frameborder="0" allowfullscreen></iframe></div>