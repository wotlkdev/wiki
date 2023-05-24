---
layout: default
title: Your First Model Edit (Unfinished)
nav_order: 4
---

# Your First: Model Edit (Unfinished)

This guide will teach you the very basics of customizing 3D models in Blender using the WoW Blender Studio Addon.

We will learn how to:
- Set up WoW Blender Studio
- Make a minor modification to a WMO file
- Make a minor modification to a static M2 file

## Theory: M2 and WMO files

Before we start setting up our extension, we need to understand the two basic file formats used to represent 3D models in WoW.

### M2

M2 files are the most common type of models in the game, and is used for things like:

- Player models
- Creatures
- Items
- Spells
- Props
- UI models

M2 models support animations, but are also commonly used without animations. Most tools do not support editing M2 animations, but working with M2 mesh data is very common even for M2s with animations.

M2 models have the `.m2` file extension, and are **always** accompanied by one or more `.skin` files in WoTLK, which contains data for viewing the model at different distances (LOD). Contrary to what many beginners believe, the `.skin` file are **not** used for creature variations.

[[image of m2 file with .skin files]]

### WMO

WMO is a type of model often used for large structures like houses, caves, bridges and even capitals like Stormwind and Orgrimmar.

WMOs support a lot of things useful for large map objects, like **culling portals**, that improve rendering performance and things like **vertex colors** that allow you to paint colors on top of textures to simulate light.

WMOs have the `.wmo` extension, and are usually grouped together by one `x.wmo` file called the **root** file, followed by one or more `x_000.wmo`, `x_001.wmo`, `x_002.wmo` files, called **group files**. When opening a wmo file in WBS, we always select the **root** file.

[[image of root wmo with some group files]]

## Learning to use Blender

Since most model editing for WoW is with Blender, this tutorial will assume you understand Blender basics, like navigating the 3D viewport and editing vertices.

You can learn Blender from here:
- Blender Guru
- [[Add more here]]

You can skip these topics entirely:
- Rendering

For the purpose of trying out WBS, these sections are also not strictly necessary but might be useful for the future:
- UV unwrapping
- Texture editing
- Sculpting
- Scripting
- Material Editor

## WoW Blender Studio (WBS)

[[WRITE IT]]