# Your First: Data Edit

_Disclaimer: This article is written by one of the authors of TSWoW._

Data editing refers to adding or changing entries in the clients and servers data tables. This is used for modifying or creating things like:

- Items
- Spells
- Professions
- Classes
- Races
- And much more

## Prerequisites

To follow this tutorial, you should have completed the following tutorials (or have an equivalent setup ready):

- [[Your First Client Edit]]
- [[Your First Server]] (alternatively, [[Choosing a Core]])

## Data Tables

There are two types of data tables that we can edit in the game, **DBC** files and **SQL** tables.

* **DBC files** are binary files that come from the clients MPQ archives, but are used by both the client and server for custom projects.

* **SQL tables** are tables hosted in an SQL database and are only used by the server.

Some entities in the game are defined in DBC files, while others are defined in SQL tables. For example, **Spells** are defined in the DBC file `Spells.dbc`, while creature types are defined in the SQL table `creature_templates`

[[Images showing a dbc file and an sql table]]

## Approaches

There are three common approaches to data editing, **Table editors**, **Designers** and **TSWoW**.

* **Table Editors** are programs that allow you to edit the raw data tables rows and columns. SQL tables and DBC files have separate editors
    * _Examples: [[WDBX]] (DBC), [[HeidiSQL]] (SQL)_

* **Designers** [[what to call these???]] are programs specifically written to make editing some types of tables easier, such as Spells or creatures. There aren't such hand-tailored tools available for all tables in the game, so these are commonly used together with _Table Editors_.
    * _Examples: Spell Editor, Keira3 [[more examples!!]]_

* **TSWoW** is a special [[server core]] that uses a completely different approach to data editing by using a special scripting language. TSWoW has simplified editing for far more tables than most _Designer_ tools do today, but relies on scripting and can generally not be used together with other data editing tools.

This tutorial will focus on using **Table Editors**, but may still be useful for Designer or TSWoW users who wants to understand how these tables work behind the scenes.

## Your First: SQL Edit

TBD

## Your First: DBC Edit

TBD