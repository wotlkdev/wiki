---
layout: default
title: Server Files
nav_order: 2
---

# Server Files

The server files are all the files used by the server aside from the core itself and its databases. 

## Configuration Files

For most emulators, the core uses two configuration files, the `worldserver.conf` and the `authserver.conf`. Some custom projects and extensions create their own custom `.conf` files, while others simply extend the `worldserver.conf`.

For how to use these configuration files, refer to your cores documentation.

## Extract Data

Extractors, or Tools, are special programs built with the server core to extract data from the client that the server needs. For how to extract these files for your own core, refer to their documentation. The rest of this document will only explain what these files are and what they actually do.

There are generally four types of files extracted/generated from the client: DBC files, MAP files, VMAP files and MMAP files

Despite their names, extractors do not only just extract data, but also process it into new filetypes. DBC files that are extracted are read exactly the way they are written in the client, but MAP/VMAP/MMAP data is produced by processing other file types in the client, and there are **no MAP/VMAP/MMAP files inside the client itself**.

### DBC Files

See the [DBC Files](./dbc) article. These are the exact same DBC files used by the client itself so the server is aware of the data in them.

DBC files are **required** to extract for the server to function at all.

### MAP Files

These are files that contain basic data used to calculate the games **heightmap**, as well as data to figure out what parts of the world is **underwater** and where to apply **fatigue** flags.

Map files are generated from the clients [ADT](./adt) files.

Map files are **required** to extract for the server to function at all, but some cores do not require them to be built for all maps.

### VMAP Files

These are files that contain more complex map data used for visibility and line of sight.

VMap files are based on the clients [ADT](./adt) files, as well as the [M2](./m2) and [WMO](./wmo) files that are spawned in them.

Vmap files are **optional** to extract, and can be disabled in worldservers configuration files.

### MMAP Files

These are files that contain even more complex map data used for pathfinding.

MMap files are based on the same data as VMaps, but process them differently and often takes significantly longer to extract.

MMap files are **optional** to extract.