---
layout: default
title: BLP Files
nav_order: 4
---

# BLP

BLP files are used for all kinds of image files in the game, from interface files to 3D model textures and map tilesets.

The BLP format isn't one format, but actually a whole family of file formats that different texture files in the game have different requirements for.

## Pixel Format

There are two primary pixel formats used in 3.3.5 BLP files;

- Palettized:
    - Images have a limited (maximum 256) colors they can display.
    - Often required for things like character skins and cloth textures, meaning those textures often look worse than other things in the game.

- RBG:
    - Commonly referred to as "DXT", coming from the [compression algorithm](https://en.wikipedia.org/wiki/S3_Texture_Compression) they use.
    - Used for most things in the game
    - Supports millions of colors in RGB format.

## Alpha Depth

Alpha refers to how transparent a pixel is on an image. Both Palettized and DXT BLPs support three alpha 'bit depths', meaning how many bits are used to represent alpha values on a single pixel:

- **0 bit**: Alpha not supported
- **1 bit**: Pixel is either completely visible or invisible
- **2 bit**: Pixel can be partially visible, with a total of 256 possible visibility levels.

## Mipmaps

Mipmapping is a technique used in video games primarily to [reduce aliasing](https://en.wikipedia.org/wiki/Mipmap), and is used and sometimes even required for some types of images in the game.

If it seems like a texture you've added to the game has bizarre random pixels inbetween other pixels, or just looks extremely glitched out, it's likely that it does not have mipmaps correctly added.

## Dimensions

Many textures in the game requires blp images to be specific dimensions (commonly 256x256 pixels) or at least powers of two (1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192 and so on).

## Editing BLP Files

BLP files are commonly converted into pngs using [BLPLab](https://www.hiveworkshop.com/threads/blp-lab-v0-5-0.137599/) or in Photoshop (CS6) using the [BLP Plugin](https://www.wowinterface.com/downloads/info22445-BLPFormatPlug-inforPhotoshop.html)