---
layout: default
title: Server Programming
nav_order: 5
---

# Server Programming

WoW is an online game that requires a server to function at all. Because of how complicated WoW is, creating a server from scratch is a monumental task that virtually nobody bothers doing anymore. Instead, we use one of the available open source servers as a basis to further customize our game by changing their existing programming for our needs. This server "base" is often referred to as the server **emulator** or **core**.

Server programming commonly comes in two basic categories:

- **Scripting**, which involves writing small extensions that reacts to events in the server core, often in a beginner-friendly language like **Lua** or **TypeScript**. Since scripting cannot modify all the internal workings of the server it comes with some limitations, but for many servers scripting is more than enough to achieve very customized results and with good enough performance for the vast majority of servers.

- **Core Programming**, which involves changing the **internal programming** of the server to fix bugs or to change how the game works at a fundamental level. This is done more or less exclusively with **C++**, and is significantly less beginner-friendly than scripting. Core editing is often used for the types of edits that scripts are not flexible enough to do, to fix internal bugs or for systems that are called very often and require very high performance.

<table class="gt" style="table-layout: fixed; width: 100%;">
    <tr>
        <td><p><img class="mi" src="https://i.imgur.com/yZuVnny.png">Eluna is a popular library used to write server scripts using Lua</p></td>
        <td><p><img class="mi" src="https://i.imgur.com/818iIaN.png">Core programming is done using C++</p></td>
    </tr>
</table>
