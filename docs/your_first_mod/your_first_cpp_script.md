---
layout: default
title: Your First C++ Script (Part 1) (UNFINISHED)
nav_order: 5
---

# Your First C++ Script (Part 1) (UNFINISHED) - Creating the Files

This tutorial will go over creating your first TrinityCore C++ script, and explaining everything step by step.
Some of you may find C++ scary, but don't worry, it's scary because lots of people code in a perverse, scary way.
It can actually be easy to write, simple to understand, and intuitive. And that is how this tutorial shall be. Hopefully.

You will create a script which will: 

* Create and manage a timer
* Keep count of all the different units of time that have passed (seconds, minutes, hours, etc.)
* Do 99% of the work on a separate thread, rather than the single world thread.
  - Scary? Not if you follow this tutorial. 
   * Unnecessary? Probably, but we're here to learn.
* Create a new table entry in the WorldServer's MySQL database
* Load data from the MySQL database
* Save data to the MySQL database

Note: This guide assumes you:
* Followed the procedure of compiling your server, so you have the necessary software already installed.
* When you ran CMake, you set the following (for TC, ignore for AC):
  - `Scripts` is set to `Dynamic`
  - `WITH_DYNAMIC_LINKING` is enabled

## Using Visual Studio

Visual Studio is the main tool that you will be using to create your own edits, and additions, to the server source code. For now, this tutorial will focus on TrinityCore, but should apply to AC as well. In the future, it will be updated for TSWoW as well.

<img class="mi ili" src="https://i.imgur.com/DolCXNL.jpg">

First, launch Visual Studio via the solution created by CMake. For TrinityCore, this will be called `TrinityCore.sln`.
* Any edits made to the source files in the solution (in CMake's `Build` folder) will also be made to the original source files (CMake's `Source` folder).
  - This means you do not need to copy files back and forth.

## TrinityCore's Structure

For the scope of this tutorial, we will: 
* Modify and add files in the `scripts_world` project tree
* Modify `Server\Game\Entities\Player\Player.cpp`

The edits made to the various `scripts` projects will be compiled to a separate `.dll`, which allows us to only compile those files, rather than the entire server executable. This saves a huge amount of time, otherwise you would have to compile not just the script project(s) you modified, but then everything else as well. For every change.

That is very slow. Unfortunately, AzerothCore does not support separate .dll files for the script projects. It does have a system called `Modules`, but that is out of scope of this tutorial.

## Creating The Files

First thing's first. We need to create a World script .cpp file, another .cpp file which will contain our actual code, a .h header file so the World script can use it, then re-run CMake so the project will actually "know" about our new file.

## Creating a World Script

To do this:
* Navigate to the `scripts_world\World` directory
* Right-click on `World` -> `Add` -> `New Item...`

<img class = "mi ili" src="https://i.imgur.com/JITHBhn.jpg">

* Select `C++ File (.cpp)
* Type in `timescale_loader_script.cpp` for the file name
  - You can name these files whatever you want, but for sake of consistency, keep the same file name for now

<img class = "mi ili" src="https://i.imgur.com/TKrnryl.jpg">

* The file will now be present in the project tree panel on the right

<img class = "mi ili" src="https://i.imgur.com/2C1R3ts.jpg">

Note:
* This file won't do most of the processing
  - It will start the timer on server start, send out the timer's game time to all players periodically, and shutdown the timer when the server closes
* The actual timer code will be in a separate file, to keep things neat and tidy.

## Creating the Timer Code Files

The process is the very much the same as the above:
* Navigate to `game\Timer`
* Add a new .cpp file
* Name it `Timescale.cpp`
* Add a new `Header File (.h)`
* Name it `Timescale.h`
  - The header file is paired with the .cpp file of the same name.
  - It contains entries of all the functions we want to call from other .cpp files

<img class = "mi ili" src="https://i.imgur.com/WY0gfl1.jpg">

Now that we have created all three files, we now need to run CMake, in order to have our new files actually work with the existing TrinityCore ones.

All you need to do is:
* Close Visual Studio
* Launch CMake
* Click `Configure`
* Click `Generate`

<img class = "mi ili" src="https://i.imgur.com/zKvuliM.jpg">

* Open the VS project
* Right-click on `ALL_BUILD`
  - -> Select `Clean`
* Wait for VS to finish cleaning the project
  - This removes any leftover files from the CMake process

<img class = "mi ili" src="https://i.imgur.com/h6GMbrt.jpg">

--todo: Everything else