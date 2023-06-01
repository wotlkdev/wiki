---
layout: default
title: Lag Simulation
nav_order: 7
---

# Lag Simulation

When we develop mods for wow locally on our machines, we usually run the game at more or less 0ms latency since there is no distance between our client and our server.

If we are developing mechanics or challenges for players that rely on quick reactions or for multiple timed events to line up well for a visual effect, it's **very important** to make sure that those mods also work under the network conditions we're expecting for our server, which can range from anything between 50ms up to a few hundred ms if playing with people from across the world.

For windows-based development, there is a tool specifically made for this purpose called **clumsy**. Clumsy is a very simple program that allows us to simulate a wide variety of network conditions like lag and packet drop.

## Setup

Clumsy is extremely easy to set up for local development. Simply [download the latest release](https://jagt.github.io/clumsy/download.html) and extract the zip file somewhere on your computer, and then start `clumsy.exe` with admin priviliges.

To enable/disable packet capture, use the Start/Stop button (sometimes it's invisible and you need to hover your mouse over it for it to become visible). The other default settings are good enough for local wow development.

<img class="mi ili" src="https://i.imgur.com/yhx0Bwe.png">

## Lag

The "Lag" toggle allows us to enable 'reliable' latency in our application. When enabled, clumsy will hold all packets for as long as the delay specified in the "delay(ms)" field. There are three important things to note here:

- The `Inbound` checkbox is not used and its value does not matter.
- The `Outbound` checkbox **must** be enabled.
- The value in the `Delay(ms)` box becomes **two times as long** for local connections, and means most visible reactions in the clients become **four times as long**. This is because:
    - All packets are captured and intercepted twice by clumsy because of how windows handles local connections.
    - Most actions made by the client consists of two packets, one client->server packet and one server->client packet.
    - Because both the client->server packet and the server->client packet are captured twice, the noticable delay for most actions in the game are **four times as long** as the time specified..

<img class="mi ili" src="https://i.imgur.com/Gyh0RdN.png">

## Throttle

The other useful setting you can use is the `Throttle` toggle, as it allows us to both specify a delay and a chance to create more randomized delays. Because it is randomized and works by batching packets, this delay behaves more unpredictably on local connections with how much delay is actually applied to a single action, but is similarly only using the `Outbound` toggle for local connections.

<img class="mi ili" src="https://i.imgur.com/1lbtEVI.png">

## Other settings

Most other settings are rarely useful in wow development, but are documented on the [official clusmy documentation](https://jagt.github.io/clumsy/index.html).