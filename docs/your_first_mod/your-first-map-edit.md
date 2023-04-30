---
layout: default
title: Your First Map Edit
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

We will not be covering artistic techniques in this tutorial, but there are plenty of those to be found around places like Youtube and MCNet. While many are for older versions of Noggit, they motly work the same.

## Prerequisites

- [[Your First Client Edit]]
- [[Your First Server]] (alternatively, [[Choosing a Core]])

## Downloading Noggit Red

Noggit Red is still a program under heavy development, and its releases are currently posted to [this discord server](https://discord.gg/Tk2TpN8CaF) under the `#announcements` channel.

If you hate Discord or don't want to have to connect just to download the program, the latest direct downloads as of the writing of this guide is [here](https://github.com/Intemporel/NoggitRedBinaries/archive/refs/heads/main.zip), and with a patched executable [here](https://mega.nz/file/3cEjTTZC#40cKBFdlHfpUiq6tIX0r0iRU0yLW3Nkiv_u7A1Cbcmw) (just replace the one in the previous download), but please keep in mind this guide will probably not stay up to date with all the latest noggit red releases, so it's strongly recommended to join the discord if so with just a dummy account.

## Starting Noggit Red

We start the program from `noggit.exe`. This should show a screen that looks like this:

[[Image of noggit red project selection]]

We'll create a new project and give it a descriptive name.

The field `Project Path` should point at a custom MPQ folder (see [[Your First Client Edit]]), or if using TSWoW, a module `assets` directory.

The field `Client Path` should point at your client directory (the one that contains `wow.exe`)

MPQ Folder Example:

[[screenshot of mpq folder example]]

TSWoW Module Example:

[[screenshot of tswow module example]]

_Please note that while the expansion list also contains an entry for Shadowlands, this isn't even remotely working in the public version._

This will add a new project to our list, and we can **double click** it to open it.

[[screenshot of the new thing]]

Now, it should open a map selection screen after a few seconds. If we click any of the maps that show up the menu to the left, it will show up a gridded map in the main view, where we can click anywhere to open the full editor view from there. Let's check out Durotar!

[[screenshot of the map with durotar selected]]

When we click on the map for the first time, the editor will show us a dialog box to select a "UID scheme". You don't need to worry about this, just select the second option for "Fix all UIDs", and do this for every map where it asks you about it.

[[screenshot of the selection]]

Loading the map will take a while, and might even take a few minutes the first time. Once it's done, you should be presented with the main Noggit editor view.

[[screenshot of noggit itself]]

## Noggit Red Interface

There are a lot of buttons to go over here, so we will start with a basic overview before we move on to the details.

[[same screenshot but with things marked out]]

### Top: Visibility Bar

This bar allow us to toggle some view settings, like choosing to show models or grids. You can try clicking on any of these to see what they do. The last button marked in green is special, and we will get to what that one does a little later.

### Left: Tool Bar

This is the bar where we select what tool we want to work with, like **sculpting**, **texturing**, **shading** or **model placement**.

### Right: Current Tool Settings

The window to the right allow us to change settings for the tool we currently have selected. If you select different tools in the tool bar, you will see that this window changes.

## Basic 3D Navigation

To rotate the camera, hold down the **Right Mouse Button** in the 3D view and move it around.

To move the camera, make sure the 3D view is focused by clicking on it and use the WASD keys to fly around.

You can move the camera with the WASD keys and rotate it with the Right Mouse Button simultaneously for full 3D movement. These controls are the same regardless of what tool you're currently using.

## Sculpting

For sculpting, we use the two first tools in the tool bar, the **Raise / Lower** tool and the **Smooth Tool**.

### Raise / Lower Tool

The Raise / Lower tool is the one at the very top with two mountains on it.

[[screenshot of that button]]

If you move your mouse over the 3D view, you should see noggit forms a circle around it that follows the terrain. This is the brush we use to actually shape the terrain.

To raise terrain, move the mouse button over the 3D view, **hold down shift** and then hold down the left mouse button. You should see the terrain raise where you held your mouse.

[[screenshot of heightened terrain]]

To lower terrain, we do the same thing but instead **hold down the control key**.

[[screenshot of lowered terrain]]

The menu to the right allows us to select different settings for our brush.

* **Type**: Selects a mathematical formula to use for sculpting. These names don't make a lot of sense on their own, but you can try out different ones to see what kind of effect they give.

* **Radius**: Determines how big your brush is

* **Inner Radius**: For some brush types like **Gaussian**, decides things like brush falloff, and is expressed as a ratio (0-1) of the full radius. Not all brush types use this.

* **Speed**: Determines how fast your brush lowers or raises the terrain.

### Smooth Tool

The smooth tool is the one right below the Raise/Lower tool with a dashed line.

This tool is very similar to the sculpting tool in that it allows us to select a **Type** and brush settings.

Painting with the smoothing tool is the same as with the Raise / Lower tool, we use **shift + left click** to 'increase' and **ctrl + left click** to 'decrease'. You can try these brushes out for yourself to see how they work more precisely.

## Texturing

The texturing tool is the one right below the _Smoothing Tool_ with a paintbrush icon. Texture painting is more complicated than sculpting, so we need to go over a little about how terrain textures work in World of Warcraft.

### Texture Layers

Terrain textures are made up of up to 4 separate layers of textures that the game displays on top of the terrain. The textures themselves are small image files that are simply repeated across the terrain for as far as they are painted, a process known as _tiling_.

[[some illustration of this]]

But, surely, the terrain of an entire map consists of more than 4 textures, the textures in the Barrens are completely different from those in Durotar or Ashenvale.

The game achieves this by dividing up the map into square pieces called **chunks**, each with its own unique set of up to 4 textures.

You can visualize the maps chunks by clicking the **Grid** button in the top view menu. This will show some red lines and some green lines on the map. Each square made up by the smaller red lines is a **chunk**.

[[illustration of the view button and showing what a chunk is]]

### Viewing Chunk Textures

To see what textures are present in a chunk, we can hover the mouse over it with the Texture Painter tool and press **ctrl + left click**. This will bring up a menu like this:

[[texture menu]]

These are the texture files currently present in this chunk and in what order they are painted.

### Texture Palette

To paint a new texture on the terrain, we can either select it from the chunk texture menu we just discussed by clicking on it, or we can choose from a list of all textures available in the game. This is done by clicking this icon in the right menu:

[[screenshot highlighting current texture image]]

Here, we can select any texture we want or search for a texture in the small text box in the top right. When we select a texture, you'll notice that it shows up in the little square we just clicked on.

### Painting Textures

Now that we have selected a texture we can paint it out onto the world. This is done by moving our mouse into the 3D view and **shift-click** onto the ground.

If you have the chunk view on, you might notice that it is not possible to paint your texture onto some chunks. This is becasue those chunks already have 4 textures on them, and it's not possible to add another due to limitations in the games file formats.

Just like with the previous tools, there are a few options in the tool menu. These are mostly self-explanatory and you can figure out what they do by toying around with them a little.

### Replacing Textures

If a chunk has too many textures and we want to add another to it, we will need to **replace** an existing texture. This is done using the **Swap** tool in the texture painter menu.

[[show the swap menu with the button highlighted]]

This tool is a little unintuitive, so follow closely.

Let's say that we have a chunk like this, and we want to replace the first texture.

[[screenshot of the texture picker and the chunk it's in clearly visible]]

First, we select the texture into the topmost texture window

[[show the first texture selected into the window]]

Now, we press the "Select" button to tell Noggit that this is the texture we want to replace **From**.

[[show the first texture selected into the second window]]

Now, we can click on the first button and select a new texture that we want to replace **to**:

[[show the texture viewer and the square we clicked to open it]]

Now that we have a texture to replace from and one to replace to, we can simply swap it by **shift-clicking** any chunk with the _from_ texture in it, and we will replace that texture. 

[[show the texture replaced in noggit]]

We can also do the same thing in neighbouring chunks:

[[show more chunks with the new texture]]

## Object Placement

To place objects into the world, we use the _Object Editor_ tool. This is the button that looks like an isometric 3D cube in the tool selector:

[[show that cube]]

### Selecting, Moving, Rotating, Scaling Objects

Before we start, we want to make sure that the **Drag Selection Depth** setting is set to something higher than 100, because that's a very low setting. Put it to something like 2000 instead:

[[show that setting]]

We can select objects in the Object editor simply by clicking on them in the 3D view, or select multiple object by dragging our mouse over all of them.

Once we have one or multiple obejcts selected, we should see a 3D gizmo on it that allows us to move the object around by dragging on them:

[[show the thing]]

In the Object Editor, there is a new menu just below the visibility panel that allows us to select different 3D gizoms.

**First Icon**: Toggles the 3D gizmo itself.
**Secon Icon**: Toggles if the gizmo should be aligned to the world coordinate system or the models own rotated coordinate system.
**Third Icon**: Activates gizmo to move the model around
**Fourth Icon**: Activates gizmo to rotate the model
**Fifth Icon**: Activates gizmo to scale the model

### Unscalable Objects

If you try and scale a few different models, you might notice that some of them are possible to scale while others are not.

This is because there are two types of 3D models in the world: M2s and WMOs.

M2s are usually smaller objects like fences, trees or bushes, while WMOs are usually bigger objects like houses or caves.

M2s can be scaled, but WMOs cannot. If you try to scale an object and are unable to, it's almost certainly because it's a WMO and not an M2.

### Adding Objects

To add new objects to the world, we can use Noggit Reds Asset Browser, which you can open from the object placer menu:

[[show asset browser button and the asset browser open]]

This window allows us to easily browse the model files available in the game. Most of the assets that are relevant to place into the world are found in the `world` directory:

[[show world directory selected with an object selected inside it]]

When we have selected an object in this menu, we can place it into the world by moving our cursor over to the 3D view and pressing `ctrl + v`.

## Saving our Changes

When we have made the changes we want to the world, we can save them either by pressing `CTRL + S` or in the `Editor` window menu and selecting `Save Changed Tiles`.

## Summary

In this tutorial, we have learnt:

- Setting up Noggit Red
- Sculpting
- Texturing
- Object placement
- Reloading our edits in the client

There are still things to learn about map editing, such as how to get our map changes into the server for things like pathfinding, visibility and fatigue calculations.

Since such workflows are specific for different cores, we will not cover them here.

[[If someone feels like writing this for AzerothCore / TrinityCore feel free to]]