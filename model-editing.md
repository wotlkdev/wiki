# Model Editing

Model editing in wow is primarily done in **Blender**, using one of two extensions:

1. M2Mod
    - Used for modifying the mesh data (triangles and vertices) of animated or otherwise complex M2s
2. WoW Blender Studio
    - Used for modifying and creating WMOs and non-animated M2 models.

This guide will focus on WoW Blender Studio, as it has a much broader use than M2Mod and may eventually replace it if it manages to fully support animated and character models in the future.

## Introduction to WoWs model file formats

The 3.3.5 client uses two file formats to represent model data for different purposes:

## WMO

WMO is a special type of model often used for large structures like houses, caves, bridges and even capitals like Stormwind and Orgrimmar.

WMOs support a lot of things useful for large map objects, like culling portals that improve rendering performance and things like vertex lightning that allow you to paint colors on top of textures to simulate light.

WMOs come in the `.wmo` format, and are usually grouped together by one `x.wmo` file called the **root** file, followed by one or more `x_000.wmo`, `x_001.wmo`, `x_002.wmo` files, called **group files**. All you need to know about these different files at this point is that you need to move them around together, and if a program asks you to import one of them, you should select the **root** file.

## M2

M2 files are the most versatile model format, and is used for everything that is not a WMO, such as player models, creatures, items, spells, game objects and smaller props in the world.

M2 models can be either animated and non-animated. Non-animated M2s are significantly easier to work with than animated ones, and to this day many tools still struggle to handle animated M2s correctly.

M2 models come in the `.m2` format, and are **always** accompanied by one or more `.skin` files, which contains data for viewing the model at different distances (LOD for those technically minded).

Contrary to what many beginners believe, the `.skin` file does **not** contain texture data or creature variations.

## Learning to use Blender

As most model editing for WoW is done using Blender, the following sections will assume basic knowledge of using it.

If you need to learn Blender from scratch, there are plenty of excellent tutorials on Youtube from channels like Blender Guru.

For the purposes of WoW modding, you can comfortably skip features like "rendering", because we don't use that at all in WoW modding. Other features, like sculpting, may have some use, but is not a core requirement by any means.

## WoW Blender Studio (WBS)

This will be a basic tutorial for setting up and getting started with wow blender studio to create a simple wmo model and a simple m2 model.

It will not teach you all the features available in WBS, and may have slight inaccuracies as WBS is still a program under heavy development.