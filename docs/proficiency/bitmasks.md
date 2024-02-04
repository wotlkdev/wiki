---
layout: default
title: Bitmasks
nav_order: 10
---

# Bitmasks

In WoW modding, you will often encounter a concept called **bitmasks**. Beginners often struggle to understand bitmasks, because the way most programs represent them has very little to do with what they actually are.

Examples of bitmasks in the game include **classmasks**, **racemasks**, **spell effect masks** and **phases**. Despite their different names and the specific functionality they provide, these all fundamentally work the same way, and once you understand one you should be able to easily understand the others.

The goal of this tutorial is to explain what bitmasks are used for, why they often look like ridiculous huge decimal numbers, and what kind of data they _really_ contain.  

## What Bitmasks Are

Bitmasks might look like numbers in most database and dbc editors, and in a technical sense they _are_ numbers, but they aren't really used for counting.

Bitmasks are _lists of boolean (true/false)_ values. Nothing more and nothing less.

## How Bitmasks Work

The reason bitmasks often looks like nonsense is because they do not represent a decimal number, but a **binary** number. Most database / DBC editors just display them as decimal numbers because it's easier (for them).

An easy way to reveal the true form of a bitmask is through the `Programmer` mode of the Windows Calculator.

<img class="mi ili" src="https://i.imgur.com/8YcsiLx.png">

Here, we can easily convert a decimal number to its binary counterpart by selecting the `DEC` line and typing our number in. The binary number will then appear under the `BIN` line.

<img class="mi ili" src="https://i.imgur.com/VWL9goJ.png">

<img class="mi ili" src="https://i.imgur.com/gpR3Q10.png">

In our case, we converted the decimal number `7523` to the binary number `0001 1101 0110 0011`.

### Lists of 0/1 values

Bitmasks are not just any binary number, but use the binary number system to represent a **list** of true/false values. For programmers, you can think of a bitmask as a way to abuse binary numbers to represent a very compact array of booleans. 

In the above example, we had the binary number `0001 1101 0110 0011`. Counting right to left, the 0th, 1st, 5th, 6th, 8th, 10th, 11th and 12th digits have values 1, with all other digits being 0.

This is the true purpose of a bitmask. In the above example, we say it is a list of booleans where indices 0, 1, 5, 6, 8, 10, 11 and 12 are true, because those are the binary digits with values of 1.

### The Size of a Bitmask

Just like other lists, bitmasks can theoretically have any size, but the fields we work with in the game always have a **fixed** size. Most bitmasks in the game are implemented as 32-bit numbers, so their size is always 32, but there are some rare fields with sizes of 64 or 96.

It's important to remember that this is not just a maximum size of the bitmask, but a **fixed** size that it **always** has. If we write a 32 bit number as `1101 1111`, it's real value is always the full `0000 0000 0000 0000 0000 0000 1101 1111`, and the leading zeroes are still important, just "false".

### Digit Indices

When we deal with bitmasks, we are often interested in the 0/1 value of a specific digit in the mask, and by convention we refer to the first element as the `0th`. For example, in the bitmask `0101`, the 0th digit (counting from the right) is 1, the 1st digit is 0, the 2nd digit is 1, and the 3rd digit is 0.

The `0th`, `1st`, `2nd` and `3rd` part is referred as the "index", and works just like an index into any other list.

Because bitmasks are used for various different purposes, these indices have various different names that all mean the same thing:

- Index
- Digit index
- Bit index
- Flag
- Channel

## Bitmask Operations

Since bitmasks are often implemented as normal numbers, we can apply mathematical operations like `+`, `-`, `*` and `/` to them. However, doing so will usually lead to unexpected results and should be avoided, `+` is especially treacherous and should never be used on bitmasks.

When working with bitmasks, there are **two** operators we need to be aware of. Once we understand how these operators work and what the game uses them for, we will finally understand why bitmasks are so useful. 

### Union / Binary OR

The first operator is the **union** operator, also called the **binary or** operator. Its purpose is to take two bitmasks and produce a third that has all bits set that are set in **either** of the input bitmasks.

The most common symbol for bitmask unions is the `|` symbol.

For example: `0001 | 0010 = 0011`. The 0th bit comes from the first operand, and the 1st bit from the second.

A few more examples:

- `0001 | 0001 = 0001`
- `0011 | 0001 = 0011`
- `0001 | 0000 = 0001`
- `1111 | 1111 = 1111`
- `1000 | 0001 = 1001`

### Intersection / Binary AND

The second operator is the **intersection** operator, also called the **binary and** operator. Its purpose is to take two bitmasks and produce a third that has all bits set that are set in **both** of the input bitmasks.

The most common symbol for bitmask intersection is the `&` symbol.

For example: `0001 & 0011 = 0001`. Only the 0th bit is present in both inputs, so it's the only one kept in the result.

A few more examples:

- `0001 & 0001 = 0001`
- `0001 & 0010 = 0000`
- `1111 & 1111 = 1111`
- `0001 & 0000 = 0000`
- `1111 & 0000 = 0000`

As you might have noticed, the `&` operator is the inverse of the `|` operator, and does to 0s what `|` does to 1s.

## Bitmasks in World of Warcraft

In this section, we will go over some of the common examples and uses of bitmasks in the game.

### ClassMasks

One of the most common uses of bitmasks in the game is to represent a group of classes or races.

In the game, classes have ids between 1 (Warrior) and 11 (Druid). To represent a class in a bitmask, we take its ID, subtract 1, and use that number as the **bit index** into the bitmask.

For example, since **Warriors** have class ID **1**, it is represented in a classmask at index ```1 - 1 = 0```. The classmask `0000 0000 0000 0000 0000 0000 0000 0001` represents the set of classes containing only Warriors.

Since **Paladins** have class ID **2**, they are represented at index `2 - 1 = 1`. The classmask `0000 0000 0000 0000 0000 0000 0000 0000 0010` represents the set of classes containing only Paladins.

To represent the set of classes containing Paladins **and** Warriors, we can therefore use the classmask `0000 0000 0000 0000 0000 0000 0000 0000 0011`, where we set both the 0th and 1st digits to 1.

The below table shows all classes in the game and their classmask values in both decimal and binary.

| **Class**    | **Class ID** | **Classmask (Decimal)** | **Classmask (Binary)**                  |
|--------------|--------------|-------------------------|-----------------------------------------|
| Warrior      | 1            | 1                       | 0000 0000 0000 0000 0000 0000 0000 0001 |
| Paladin      | 2            | 2                       | 0000 0000 0000 0000 0000 0000 0000 0010 |
| Hunter       | 3            | 4                       | 0000 0000 0000 0000 0000 0000 0000 0100 |
| Rogue        | 4            | 8                       | 0000 0000 0000 0000 0000 0000 0000 1000 |
| Priest       | 5            | 16                      | 0000 0000 0000 0000 0000 0000 0001 0000 |
| Death Knight | 6            | 32                      | 0000 0000 0000 0000 0000 0000 0010 0000 |
| Shaman       | 7            | 64                      | 0000 0000 0000 0000 0000 0000 0100 0000 |
| Mage         | 8            | 128                     | 0000 0000 0000 0000 0000 0000 1000 0000 |
| Warlock      | 9            | 256                     | 0000 0000 0000 0000 0000 0001 0000 0000 |
| Druid        | 11           | 1024                    | 0000 0000 0000 0000 0000 0100 0000 0000 |

### RaceMasks

RaceMasks work almost identically to ClassMasks, just with Race IDs instead of Class IDs. To get the bitmask index of a race you take the ID and subtract 1. Below is the table of racemasks for the playable races in the game.  

| **Race**  | **ID** | **Mask (Decimal)** | **Mask (Binary)**                       |
|-----------|--------|--------------------|-----------------------------------------|
| Human     | 1      | 1                  | 0000 0000 0000 0000 0000 0000 0000 0001 |
| Orc       | 2      | 2                  | 0000 0000 0000 0000 0000 0000 0000 0010 |
| Dwarf     | 3      | 4                  | 0000 0000 0000 0000 0000 0000 0000 0100 |
| Night Elf | 4      | 8                  | 0000 0000 0000 0000 0000 0000 0000 1000 |
| Undead    | 5      | 16                 | 0000 0000 0000 0000 0000 0000 0001 0000 |
| Tauren    | 6      | 32                 | 0000 0000 0000 0000 0000 0000 0010 0000 |
| Gnome     | 7      | 64                 | 0000 0000 0000 0000 0000 0000 0100 0000 |
| Troll     | 8      | 128                | 0000 0000 0000 0000 0000 0000 1000 0000 |
| Blood Elf | 10     | 512                | 0000 0000 0000 0000 0000 0010 0000 0000 |
| Draenei   | 11     | 1024               | 0000 0000 0000 0000 0000 0100 0000 0000 |

### Checking for Eligibility

Many things in the game are only available to players of specific classes or races, such as horde quests only being offered to horde players, some Durotar quests only being offered to Orcs and Trolls and so on. 

These systems all use classmasks and racemasks to very efficiently compare a players class and/or race against an arbitrary combination of eligible classes/races.

Let's imagine we wanted to make a quest that is available only to Orc and Troll Warriors. For this, we will need both a ClassMask to represent "Warriors" and a RaceMask to represent "Orcs and Trolls".

For the "Warrior" part, it is simple enough to look up the warrior classmask in the table for the value `0000 0000 0000 0000 0000 0000 0000 0001` and we are done, that's our classmask.

For the "Orcs and Trolls" part, we will need to use what we learnt about the `|` operator to _combine_ the racemasks of Orcs and Trolls:

`0000 0000 0000 0000 0000 0000 0000 0010 | 0000 0000 0000 0000 0000 0000 1000 0000 = 0000 0000 0000 0000 0000 0000 1000 0010`

Now, we get to the good part. When the game is trying to offer the available quests at a questgiver, it will take the players own classmask and racemask and check for overlap with the quests classmask/racemask using **only a single operation each**, namely the `&` operator, and then check if the result is 0 or not. If it is 0, it means the overlap check failed, and the quest should not be offered

Let's imagine we had a player playing an Undead Warrior.

This player would have the racemask `0000 0000 0000 0000 0000 0000 0001 0000` and the classmask `0000 0000 0000 0000 0000 0000 0000 0001`.

When they encounter the questgiver, the game will first check the classmask for overlap:

`0000 0000 0000 0000 0000 0000 0000 0001 & 0000 0000 0000 0000 0000 0000 0000 0001 = 0000 0000 0000 0000 0000 0000 0000 0001`

Because the result is not 0, the classmask test passes. This makes sense, since the player is a Warrior.

Then, the game will check the racemask for overlap:

`0000 0000 0000 0000 0000 0000 1000 0010 & 0000 0000 0000 0000 0000 0000 0001 0000 = 0000 0000 0000 0000 0000 0000 0000 0000`

This result is 0, and the racemask test fails. This makes sense, since the player is neither an Orc or a Troll.

This is why bitmasks are so popular. They use extremely little memory and extremely cheap operations to do **overlap checks**.

### Bit indices and "channels"

Bitmasks do not on their own define any particular meaning to specific digit indices. Their meaning depends on what the bitmask is used for.

For some bitmasks in the game, like ClassMasks and RaceMasks, this meaning is fixed and **always** corresponds to specific class/race ids, since that's what the game uses them for. If you see a ClassMask somewhere in the games data, you always know exactly what it means.

For other bitmasks, the "meaning" of digit indices can be **arbitrary** or **local**. Phases is one such example, where phase indices have different meanings depending on where in the game your character is located. Here, they function similarly to radio frequencies in the real world, where different radio stations can use the same frequencies in different locations.   

For this reason, bitmask bit indices are sometimes referred to as **channels**, especially when their use is arbitrary or local.

## Summary

- Bitmasks are used to represent fixed-size lists of boolean values by abusing bit patterns in common number types, like 32-bit integers.

- The reason bitmasks often look like nonsensical large numbers is because most viewers show them as **decimal** numbers even though they only really make sense when read as **binary** numbers.

- Bitmasks use two common operators, `|` for **combining** bitmasks and `&` for creating intersections.

- What bitmasks are so good at is checking for **overlap** in lists of booleans using the `&` operator and comparing the result to 0.

- For some bitmasks in the game, like ClassMasks and RaceMasks, bit indices have fixed meanings corresponding to specific class/race ids. For other bitmasks, the choice of indices is **arbitrary** or **local**.

- The indices of binary digits in bitmasks are sometimes called _bit indices_, _digit indices_, _flags_ or _channels_. These all mean the same thing.