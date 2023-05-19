---
layout: default
title: Your First Map Edit
nav_order: 2
---

# Your First: Map Edit

This tutorial will teach you how to use the program "Noggit Red" to modify an existing map in World of Warcraft. We choose to start with an existing map because it requires slightly less steps to set up, but most of what you will learn here will also apply once you learn how to create completely new maps as well.

If you are an old Noggit user, this guide might also be useful to see all the new features in Noggit Red.

The tutorial will cover:

- Project Creation
- Sculpting (changing the shape of the terrain)
- Texturing
- Shading
- Placing Objects

We will not be covering artistic techniques in this tutorial, but there are plenty of those to be found around places like Youtube and MCNet. While many are for older versions of Noggit, they will mostly work the same regardless of version.

## Prerequisites

- [Your First Client Edit](./your_first_client_edit)
- [A server core](../server_setup/core_short)

## Downloading Noggit Red

Noggit Red is still a program under heavy development, and its releases are currently posted to [this discord server](https://discord.gg/Tk2TpN8CaF) under the `#announcements` channel.

If you hate Discord or don't want to have to connect just to download the program, the latest direct downloads as of the writing of this guide is [here](https://github.com/Intemporel/NoggitRedBinaries/archive/refs/heads/main.zip), and with a patched executable [here](https://mega.nz/file/3cEjTTZC#40cKBFdlHfpUiq6tIX0r0iRU0yLW3Nkiv_u7A1Cbcmw) (just replace the one in the previous download), but please keep in mind this guide will probably not stay up to date with all the latest noggit red releases, so it's strongly recommended to join the discord if so with just a dummy account.

## Starting Noggit Red

We start the program from `noggit.exe`. This should show a screen that looks like this:

<img class="mi ili" src="https://i.imgur.com/gsvmEJN.png">

We'll create a new project and give it a descriptive name.

The field `Project Path` should point at a custom MPQ folder (see [Your First Client Edit](./your_first_client_edit)), or if using TSWoW, a module `assets` directory. It cannot point at an actual MPQ archive.

The field `Client Path` should point at your client directory (the one that contains `wow.exe`)

MPQ Folder Example:

<img class="mi ili" src="https://i.imgur.com/QC075sF.png">

TSWoW Module Example:

<img class="mi ili" src="https://i.imgur.com/OJn63hU.png">

This will add a new project to our list, and we can **double click** it to open it.

<img class="mi ili" src="https://i.imgur.com/RtW6uU7.png">

Now, it should open a map selection screen after a few seconds. If we click any of the maps that show up the menu to the left, it will show up a gridded map in the main view, where we can click anywhere to open the full editor view from there. Let's check out Mulgore!

<img class="mi ili" src="https://i.imgur.com/xmYYCc4.png">

When we click on the map for the first time, the editor will show us a dialog box to select a "UID scheme". You don't need to worry about this, just select the first option for "Get max UID", since we haven't edited this map.

<img class="mi ili" src="https://i.imgur.com/iRajfbu.png">

Loading the map will take a while, and might even take a few minutes the first time. Once it's done, you should be presented with the main Noggit editor view.

<img class="mi ili" src="https://i.imgur.com/HyPYsau.png">

## Noggit Red Interface

There are a lot of buttons to go over here, so we will start with a basic overview before we move on to the details.

### Top: Visibility Bar

This bar allow us to toggle some view settings, like choosing to show models or grids. You can try clicking on any of these to see what they do. The last button marked in green is special, and we will get to what that one does a little later.

<img class = "mi ili" src="https://i.imgur.com/pQWkg1m.png">

### Left: Tool Bar

This is the bar where we select what tool we want to work with, like **sculpting**, **texturing**, **shading** or **model placement**.

<img class = "mi ili" src="https://i.imgur.com/rDHwAvx.png">

### Right: Current Tool Settings

The window to the right allow us to change settings for the tool we currently have selected. If you select different tools in the tool bar, you will see that this window changes.

<img class = "mi ili" src ="https://i.imgur.com/iUrIjXI.png">

## Basic 3D Navigation

To rotate the camera, hold down the **Right Mouse Button** in the 3D view and move it around.

To move the camera, make sure the 3D view is focused by clicking on it and use the WASD keys to fly around.

You can move the camera with the WASD keys and rotate it with the Right Mouse Button simultaneously for full 3D movement. These controls are the same regardless of what tool you're currently using.

## Sculpting

For sculpting, we use the two first tools in the tool bar, the **Raise / Lower** tool and the **Smooth Tool**.

### Raise / Lower Tool

The Raise / Lower tool is the one at the very top with two mountains on it.

<img class = "mi ili" src="https://i.imgur.com/pUlqiwm.png">

If you move your mouse over the 3D view, you should see noggit forms a circle around it that follows the terrain. This is the brush we use to actually shape the terrain.

To raise terrain, move the mouse button over the 3D view, **hold down shift** and then hold down the left mouse button. You should see the terrain raise where you held your mouse.

<img class = "mi ili" src="https://i.imgur.com/h94BKBd.png">

To undo what we just did, we can press `ctrl + z`

<img class = "mi ili" src="https://i.imgur.com/g6R4uoV.png">


To lower terrain, we do the same thing but instead **hold down the control key**.

<img class = "mi ili" src="https://i.imgur.com/CiW7hi0.png">

The menu to the right allows us to select different settings for our brush.

* **Type**: Selects a mathematical formula to use for sculpting. These names don't make a lot of sense on their own, but you can try out different ones to see what kind of effect they give.

* **Radius**: Determines how big your brush is

* **Inner Radius**: For some brush types like **Gaussian**, decides things like brush falloff, and is expressed as a ratio (0-1) of the full radius. Not all brush types use this.

* **Speed**: Determines how fast your brush lowers or raises the terrain.

### Smooth Tool

The smooth tool is the one right below the Raise/Lower tool with a dashed line. This tool allow us to apply different kinds of "smoothing" to terrain.

This tool is very similar to the sculpting tool in that it allows us to select a **Type** and brush settings.

Painting with the smoothing tool is the same as with the Raise / Lower tool, we use **shift + left click** to 'increase' and **ctrl + left click** to 'decrease'. You can try these brushes out for yourself to see how they work more precisely.

<img class = "mi ili" src="https://i.imgur.com/7hqU0ZG.png">

## Texturing

The texturing tool is the one right below the _Smoothing Tool_ with a paintbrush icon. Texture painting is more complicated than sculpting, so we need to go over a little about how terrain textures work in World of Warcraft.

<img class = "mi ili" src="https://i.imgur.com/LIWiIuX.png">

### Texture Layers

The game world in World of Warcraft is made up of small square pieces called "chunks". We can visualize these chunks by clicking the "grid" button in the top view menu. This will show some red lines and some green lines on the map. Each square made up by the smaller red lines is a **chunk**

<img class = "mi ili" src="https://i.imgur.com/pAdWhE4.png">

Each chunk contains up to 4 seprate layers of textures that the game displays on top of the terrain. The textures themselves are small image files that are simply repeated across the terrain for as far as they are painted, a process known as _tiling_.

To see what textures are present in a chunk, we can hover the mouse over it with the Texture Painter tool and press **ctrl + left click**. This will bring up a menu

<img class = "mi ili" src="https://i.imgur.com/24uc3Rr.png">

These are the texture files currently present in this chunk and in what order they are painted.

### Texture Palette

To paint a new texture on the terrain, we can either select it from the chunk texture menu we just discussed by clicking on it, or we can choose from a list of all textures available in the game. This is done by clicking this icon in the right menu

<img class = "mi ili" src="https://i.imgur.com/j0ext4d.png">

Here, we can select any texture we want or search for a texture in the small text box in the top right. When we select a texture, you'll notice that it shows up in the little square we just clicked on.

<img class = "mi ili" src="https://i.imgur.com/0ofl7oe.png">

### Painting Textures

Now that we have selected a texture we can paint it out onto the world. This is done by moving our mouse into the 3D view and **shift-click** onto the ground.

If you have the chunk view on, you might notice that it is not possible to paint your texture onto some chunks. This is becasue those chunks already have 4 textures on them, and it's not possible to add another due to limitations in the games file formats.

Just like with the previous tools, there are a few options in the tool menu. These are mostly self-explanatory and you can figure out what they do by toying around with them a little.

### Replacing Textures

If a chunk has too many textures and we want to add another to it, we will need to **replace** an existing texture. This is done using the **Swap** tool in the texture painter menu.

<img class = "mi ili" src="https://i.imgur.com/66dNbWM.png">

This tool is a little unintuitive, so follow closely.

Let's say that we have a chunk like this, and we want to replace the second texture.

<img class = "mi ili" src="https://i.imgur.com/lcdmzy7.png">

First, we click the _replaced_ texture so it appears in the topmost window

<img class = "mi ili" src="https://i.imgur.com/iLjBmP0.png">

Now, we press the "Select" button to tell Noggit that this is the texture we want to replace **From**.

<img class = "mi ili" src="https://i.imgur.com/LA8HBiq.png">

Now, we can click on the first button and select a new texture that we want to replace **to**:

<img class = "mi ili" src="https://i.imgur.com/2kn9fF0.png">

Now that we have a texture to replace from and one to replace to, we can simply swap it by **shift-clicking** any chunk with the _from_ texture in it, and we will replace that texture. 

<img class = "mi ili" src="https://i.imgur.com/48jJGwF.png">

We can also do the same thing in neighbouring chunks:

<img class = "mi ili" src="https://i.imgur.com/DicLTYq.png">

## Object Placement

To place objects into the world, we use the _Object Editor_ tool. This is the button that looks like an isometric 3D cube in the tool selector:

<img class = "mi ili" src="https://i.imgur.com/brle2L5.png">

### Selecting, Moving, Rotating, Scaling Objects

Before we start, we want to make sure that the **Drag Selection Depth** setting is set to something higher than 100, because that's a very low setting. Put it to something like 2000 instead:

<img class = "mi ili" src="https://i.imgur.com/bxYNnv2.png">

We can select objects in the Object editor simply by clicking on them in the 3D view, or select multiple object by dragging our mouse over all of them.

Once we have one or multiple obejcts selected, we should see a 3D gizmo on it that allows us to move the object around by dragging on them:

<img class = "mi ili" src="https://i.imgur.com/NSS8GH7.png">

In the Object Editor, there is a new menu just below the visibility panel that allows us to select different 3D gizmos.

<img class = "mi ili" src="https://i.imgur.com/Ka2V5FJ.png">

- **Icon #1**: Toggles the 3D gizmo itself.
- **Icon #2**: Toggles if the gizmo should be aligned to the world coordinate system or the models own rotated coordinate system.
- **Icon #3**: Activates gizmo to move the model around
- **Icon #4**: Activates gizmo to rotate the model
- **Icon #5**: Activates gizmo to scale the model

### Unscalable Objects

If you try and scale a few different models, you might notice that some of them are possible to scale while others are not.

This is because there are two types of 3D models in the world: M2s and WMOs.

M2s are usually smaller objects like fences, trees or bushes, while WMOs are usually bigger objects like houses or caves.

M2s can be scaled, but WMOs cannot. If you try to scale an object and are unable to, it's beause that it is a WMO and not an M2.

### Adding Objects

To add new objects to the world, we can use Noggit Reds Asset Browser, which you can open from the object placer menu:

<img class = "mi ili" src="https://i.imgur.com/bbKc0fN.png">

This window allows us to easily browse the model files available in the game. Most of the assets that are relevant to place into the world are found in the `world` directory:

<img class = "mi ili" src="https://i.imgur.com/8oXxM5y.png">

When we have selected an object in this menu, we can place it into the world by moving our cursor over to the 3D view and pressing `ctrl + v`.

<img class = "mi ili" src="https://i.imgur.com/llkKeHM.png">

## Saving our Changes

When we have made the changes we want to the world, we can save them either by pressing `CTRL + S` or in the `Editor` window menu and selecting `Save Changed Tiles`.

<img class = "mi ili" src="https://i.imgur.com/4TuVXRr.png">

## Short note about extractors

If we change the heightmap or place models into the world, we will need to re-run our servers map/vmap/mmap extractors for changes to reflect serverside.

We will not cover the details of getting custom maps to work with extractors here, as exact steps are specific to different cores, but it usually involves placing the map files into an MPQ archive (not a folder) named `patch-4.MPQ` or `patch-5.MPQ` and re-running extractors normally.

## Summary

If we now open up the map in our client, we should be able to see all our glorious edits in-game:

<table class="gt" style="table-layout: fixed; width: 100%;">
    <tr>
        <td><p><img class="mi" src="https://i.imgur.com/HWrIUzR.png"></p></td>
        <td><p><img class="mi" src="https://i.imgur.com/meCc0Yp.png"></p></td>
    </tr>
    <tr>
        <td><p><img class="mi" src="https://i.imgur.com/3eIWHvF.png"></p></td>
        <td><p><img class="mi" src="https://i.imgur.com/4TBUGuG.png"></p></td>
    </tr>
</table>

In this tutorial, we have learnt:

- Setting up Noggit Red
- Sculpting
- Texturing
- Object placement