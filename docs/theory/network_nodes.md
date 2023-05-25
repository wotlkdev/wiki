---
layout: default
title: Network Nodes
nav_order: 1
---

# Network Nodes

In this article, we will learn about the steps and entities involved in connecting the wow client to the game as an introduction to understand the games overall architecture.

The entities we will learn about are:

- [The client](./client)
- The authserver
- [The worldserver](./core)
- [The database](./database)

<img class="mi ili" src="https://i.imgur.com/AMEWUrv.png">

## Client

The client is relatively self-explanatory. It is the part of the game that runs on the players computer, and includes all the games assets, database tables, and `wow.exe`.

## AuthServer

This is the part of the server core responsible for handling initial player connections and to present the list of realms that are available to connect to.

_Before TrinityCore, this component used to be called `realmd`, as its primary purpose is to list all the available realms._

## Worldserver

This is the part of the server core responsible for managing connections the actual game world for **a single realm**, and handles everything from character creation to chat commands and map updates.

## Database

This is the part of the server that stores both static (creature definitions, item definitions and so on) and dynamic game data (accounts, characters, achievement progress and so on).

## Connecting to the game

When the client first connects to the game, it uses the address in its `realmlist.wtf` file (located in `Data/<locale>/realmlist.wtf`, where `<locale>` is the clients localization, usually `enUS` or `enGB`).

This is the address to an `authserver`, and when the player enters their credentials into the client this is the first server that it communicates with.

<img class="mi ili" src="https://i.imgur.com/d8sX07b.png">

The authserver will then check the credentials with the database to see if this is a valid account with a correct password

<img class="mi ili" src="https://i.imgur.com/cTHo3cO.png">

If the check went well, the authserver will respond to the client by presenting the list of realms available. It might seem a little strange that the authserver responds with the worldservers IP address when they are often hosted on the exact same machine, but this is not always necessarily the case. Sometimes, the worldserver is hosted somewhere completely different, and sometimes there are multiple worldservers.

<img class="mi ili" src="https://i.imgur.com/nmZ2q73.png">

Once the player has selected a realm, they will completely close the connection with the authserver, and instead connect to a worldserver, yet again sending its username and password for another round of authentication.

<img class="mi ili" src="https://i.imgur.com/6NDV0VE.png">

Many beginners are confused with why the worldserver authenticates players again when they've already done this with an authserver. The reason for this is that it's simply the easiest way to ensure that players are who they say that they are given what we have to work with from the protocol that the client uses.

<img class="mi ili" src="https://i.imgur.com/SfMXZaE.png">

If the player provided a correct password to the worldserver, it will respond by sending the list of characters currently in the players account

<img class="mi ili" src="https://i.imgur.com/CScoKOk.png">

For the purpose of this tutorial, we'll skip the case where players might create new characters, as that's just its own round of packets that don't teach us a lot about how the protocol works in general.

So once the player has selected a character to play on and enters the game world, they send their selection to the server and displays the loading screen.

<img class="mi ili" src="https://i.imgur.com/iDiUCCT.png">

<img class="mi ili" src="https://i.imgur.com/gRJccK7.png">

<img class="mi ili" src="https://i.imgur.com/HN4Vct2.png">

Once we have loaded the player, we spawn them into the world on the server and informs the client that it can start playing.

<img class="mi ili" src="https://i.imgur.com/Dlvk7Qt.png">

Once the player has spawned, they are added to the normal gameloop on the server and will begin to send and receive commands and updates back and forth. 

<img class="mi ili" src="https://i.imgur.com/8zM6VqB.png">


Occasionally, the server will save the players data back into the database. Sometimes as a response to various special events like trades and sometimes when enough time has passed.

<img class="mi ili" src="https://i.imgur.com/SplbacF.png">