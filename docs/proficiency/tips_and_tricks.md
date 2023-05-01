---
layout: default
title: Version Control
nav_order: 7
---

# Tips and Tricks

This page can contain various tricks and tips that don't fit under any other category.

## DBC file sharing with symbolic links

It can be very annoying having to keep two sets of DBC files for the server and client when modding, since they both need to be called different things , and without adjustment we cannot fix this with settings like `worlderver.conf:DataDir`.

One way to cheat this is to set up a symlink between the `DBFilesClient` directory in our client working patch directory and the servers `dbc` directory. Symlinks are similar to shortcuts, and allow us to tell the operating system that two folders in completely different locations are actually the same folder stored in only one place on the drive.

On Windows, we can create symlinks using the following command:

```
mklink /J C:\original\path\to\folder C:\new\empty\path
```

The first path is the actual path currently containing the files we want shared, and the second path is an empty path with currently nothing in it. For example, we could create a symlink like this:

```
mklink /J C:\our\client\path\Data\patch-4.MPQ\DBFilesClient C:\our\server\path\dbc
```

_note: You need to make sure to delete the `dbc` directory before running this command_