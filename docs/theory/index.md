---
layout: default
title: Theory
nav_exclude: true
---

# Theory

This section is a top-down deeper look into the various components that makes up the game, all the way from the client to the server. It is meant to be an overview meant for beginners, and not a replacement for reading your cores documentation or the technical specifications on the [wowdev.wiki](https://wowdev.wiki).

Most things in these docs should apply regardless of what core you use, but the guides will themselves refer to [TrinityCore](https://www.trinitycore.org/).

## Table of Contents

- [**Network Nodes**](./network_nodes): How the authserver, worldserver, client and server work together to connect to the game.
    - [**Server Files**](./server_files): Server configuration files and extractors.
    - [**Database**](./database): The serverside database tables
    - [**Core**](./core): How the worldserver core functions internally.
        - [**Code Structure**](./core_code_structure): What all the different folders are in the core repository.
        - [**Game Loop**](./core_game_loop): Execution graph for the various phases the core goes through when starting up and running the game server.
        - [**Modules**](./core_modules): The different classes and singletons used to manage and represent the serverside game world
        - [**Network**](./core_network): Incoming and outgoing packets and packet handlers
        - [**Scripts**](./core_scripts): Why scripts are used, how script loading works and the kind of scripts that exist.
    - [**Client**](./client): How the client is structured and what can be done with it.
        - [**ADT/WDT/WDL**](./adt): What map files are and what they contain
        - [**BLP**](./blp): The different types of image/texture files used by the game
        - [**M2**](./m2): Smaller and animated 3D models
        - [**WMO**](./wmo): NOT WRITTEN YET!!!
        - [**DBC**](./dbc): The client database tables
        - [**Interface**](./interface): Client UI and scripting