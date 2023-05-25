---
layout: default
title: Client Issues
nav_exclude: true
---

# Client Issues

This page lists various client issues and methods to fix or compensate for them. The 3.3.5 client is an almost 15 years old 32-bit executable, which can cause various issues running on modern hardware and operating systems.

## Cannot set game to windowed mode

When changing the game to use windowed or borderless windowed mode, the screen goes black.

- **Affected OS**: `Windows 10`
- **Solution**:
  - Shut down wow completely
  - Create the file `WTF/Config.wtf` if it does not already exist
  - Add the text `SET gxWindow "1"` to the bottom of that file.
  - Start wow again. You can now set it to borderless windowed mode as well.

## Hardware cursor stuttering and framerate drops

Occasional stuttering and framerate drops when hardware cursor is enabled.

- **Affected OS**: `Windows 10`
- **Affected Graphic Cards**: `GTX 1060`, `GTX 2060`
- **Workaround**:
  - Under video settings, disable `Hardware cursor`
  - Unsure if this is still an issue in 2023.

## M1 Macs

WotLK no longer works out of the box on M1 macs, but users have reported success with emulators:

- [Parallels](https://www.parallels.com/)
- [Crossover](https://www.codeweavers.com/crossover) (possibly?)