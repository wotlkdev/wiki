---
layout: default
title: Your First Data Edits
nav_order: 3
---

# Your First: Data Edits

_Disclaimer: This article is written by one of the authors of TSWoW._

Data editing refers to adding or changing entries in the clients and servers data tables. This is used for modifying or creating things like:

- Items
- Spells
- Professions
- Classes
- Races
- **And much more**

## Prerequisites

To follow this tutorial, you should have completed the following tutorials (or have an equivalent setup ready):

- [Your First Client Edit](./your_first_client_edit)
- [A server core](../server_setup/core_short)

## Data Tables

There are two types of data tables that we can edit in the game, **DBC** files and **SQL** tables.

* **DBC files** are binary files that come from the clients MPQ archives, but are used by both the client and server for custom projects.

* **SQL tables** are tables hosted in an SQL database and are only used by the server.

Some entities in the game are defined in DBC files, while others are defined in SQL tables. For example, **Spells** are defined in the DBC file `Spells.dbc`, while creature types are defined in the SQL table `creature_templates`

<table class="gt" style="table-layout: fixed; width: 100%;">
    <tr>
        <td><p><img class="mi" src="https://i.imgur.com/JkY4YSP.png">DBC Editor</p></td>
        <td><p><img class="mi" src="https://i.imgur.com/peXdbe4.png">SQL Editor</p></td>
    </tr>
</table>

## Approaches

There are three common approaches to data editing, **Table editors**, **Designers** and **TSWoW**.

* **Table Editors** are programs that allow you to edit the raw data tables rows and columns. SQL tables and DBC files have separate editors to do this.
    * _Examples_:
        * _WDBX (DBC)_
        * _HeidiSQL (SQL)_

* **Advanced Editors** are programs specifically written to make editing some types of tables easier, such as Spells or creatures. There aren't such hand-tailored tools available for all tables in the game, so these are commonly used together with raw _Table Editors_.
    * _Examples_:
        * _Spell Editor_
        * _Keira3_

* **TSWoW** is a special server core that uses a completely different approach to data editing by using a special scripting language instead of editors. TSWoW has first-class support for far more types of entities than most `Advanced Editors` tools do today, but relies on navigating a scripting language and can generally not be used together with other data editing tools.

This tutorial will focus on using **Table Editors**, but may still be useful for Designer users who wants to understand how these tables work behind the scenes. 

_For TSWoW users: You can follow this tutorial if you want, but you should not try to make any of these changes yourself._

## Next

The rest of this tutorial is split into editing **server tables** and **client tables**:

- [Your First DBC Edit](./your_first_dbc_edit) (Client Tables)
- [Your First SQL Edit](./your_first_sql_edit) (Server Tables)