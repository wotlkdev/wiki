---
layout: default
title: Data Editing
nav_order: 7
---

# Data Editing

Many of the "things" that exist in the game, such as spells, creatures, quests, items and so on are not created through raw programming, but are specified in rows and columns in special "data tables" (think 'excel sheets' or 'SQL tables') with predefined meanings that are read by both the client and server.

There are hundreds upon hundreds of these data tables used by the game and emulators, some of them with tens or hundreds of thousands of entries. For example, all spells in the game are specified in a special file in the client called `Spells.dbc`, which is just a large table with a bunch of columns that specify what each spell in the game does. Similarly, all the types of creatures in the game are specified in a similar serverside table called `creature_template`.

Data editing has a lot of overlap with server programming, and effects created in data tables are commonly listened to by server scripts to create highly specialized effects, especially for creatures and spells.

Becoming proficient with data editing involves learning the meanings of these tables, how they relate to each others and how to use them to get the game to do what you want. Some data tables in the game are very simple to edit, while others consists of hundreds of columns and cross-references to other tables that requires specialized software to edit effectively at all.

<table class="gt" style="table-layout: fixed; width: 100%;">
    <tr>
        <td><p><img class="mi" src="https://i.imgur.com/JkY4YSP.png">WDBXEditor: Tool used to edit client database tables.</p></td>
        <td><p><img class="mi" src="https://i.imgur.com/peXdbe4.png">HeidiSQL: Tool used to edit server database tables.</p></td>
    </tr>
</table>