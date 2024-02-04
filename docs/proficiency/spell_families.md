---
layout: default
title: Spell Effect Masks
nav_order: 11
---

# Spell Families

_Note: This guide assumes basic knowledge of **Spells**, **Spell Effects** and **Auras**._

In this document I will elaborate on the [Bitmasks](./bitmasks) guide and explain how spell aura effects can affect other spells.

_Spell Family Masks are sometimes referred to as "Spell Class Masks"._

## Purpose

Some aura effects do not just target the player character, but specific spells that the player has.

A typical example is the [Improved Fireball](https://wotlk.evowow.com/?spell=11069) talent, which reduces the casting time of Fireball.

For the game to know what aura effects should affect what spells, the _Spell Family_ system is used.

## Spell Fields

There are **three** kinds of fields involved in the Spell Family system, all found in the spells `Spell.dbc` entry:

- Spell Family ID _(sometimes called Spell Class ID)_
- Spell Family Masks _(sometimes called Spell Class Masks)_
- Effect Family Masks _(one for each effect for a total of 3)_ 

Spell Family Masks and Effect Family Masks are typically split into three separate numbers with suffixes A/B/C, so in total you have the fields:

- Spell Family ID
- Spell Family Mask A
- Spell Family Mask B
- Spell Family Mask C
- Effect 0 Family Mask A
- Effect 0 Family Mask B
- Effect 0 Family Mask C
- Effect 1 Family Mask A
- Effect 1 Family Mask B
- Effect 1 Family Mask C
- Effect 2 Family Mask A
- Effect 2 Family Mask B
- Effect 2 Family Mask C

However, the A/B/C fields are not separate numbers, but in fact a single 96-bit bitmask just stacked on top of each others. This applies both to the spells family masks and all the effect masks.

## Spell Family ID

For one spell to affect another spell, they **must** have the exact same Spell Family ID. This field is an ID, not a bitmask. 

Typically, the spell family id is uniquely connected to a specific class, and for spell effects to work in the client they are **required** to correspond to a specific class, but other than that they are **arbitrary** and have no inherent meaning.

To connect a spell family to a class, set the `SpellClassSet` column in `ChrClasses.dbc`. It is only possible to have a single spell family working for a single class in the game.

## Spell Family Masks and Effect Family Masks

If a spell with a **targeting** effect has the same _Spell Family ID_ as a **target** spell, the family masks of the _effect_ is checked for overlap with the family masks of the target _spell_.

If a single bit overlaps between the targeting effect and the target spell, the effect will apply.

## The Formula

Let `S1` be a spell with:
- Spell Family ID `SI1`
- Spell Family Mask `SM1`
- A spell aura effect `E1` with effect classmask `EM1`

Let `S2` be a spell with:
- Spell Family ID `SI2`
- Spell Family Mask `SM2`

If `SI1 = SI2` and `EM1 & SM2 != 0`, then `E1` will apply to `S2`. 

Note how `SM1` is never compared with `SM2`.

<img class="mi ili" src="https://i.imgur.com/MIfGQLD.png">

## Adding new Spell Family Effects

If you want to add new spells to the game that affect other spells, you need to make sure that the spell family and bit indices you choose do not collide with any existing spells, or you will start having unintended effect overlap.

For custom classes, it is enough to pick a new unique Spell Family ID to fill out in your `ChrClasses.dbc` and then use it as an arbitrary id in your new Spells. In this case, all you need to do is make sure that your own bitmasks do not have any unintended overlap, but how you choose to do this is completely arbitrary.

For existing classes, you _also_ need to make sure that your new masks do not accidentally overlap with any existing spells, since you need to use the same spell family id as the original class if you want your effects working on the client. 

## Prioritizing Effect Channels

Because spell family ids must correspond with the `SpellClassSet` column in `ChrClasses.dbc` to work in the client, it is not possible to have more than 96 distinct "channels" of aura->spell effects within a single class. 

Some effects in the game, like mana or range modifiers, do not work at all if they don't work correctly in the client, so those kinds of effects **must** be in the same spell family as the `SpellClassSet` column for the effect to work with that class at all.

However, some effects, like damage or casting time modifiers, will only break tooltips (their bonus won't show) for a class if they use another Spell Family ID. As long as your core supports it, their effect is entirely serverside and can use any spell family ids as long as both source and target spells both have the same one.

If you find yourself running out of effect bit indices under a single Spell Family ID, you may have to prioritize the ones that break completely for your `SpellClassSet` id and use other unused ids for less important effects.

## Summary

- Spell Effects will affect other spells if both spells share the same _Spell Family ID_ and the **source effects** family masks _overlaps_ with the **target spells** family mask.

- Spell Family Masks are often represented as 3 separate 32-bit integers (commonly suffixed with A/B/C), but are in fact a single 96-bit long bitmask.

- For spell effects to work correctly client-side for a specific class, the _Spell Family ID_ must be equal to the `SpellClassSet` column in the class `ChrClasses.dbc` entry.

- Some spell effects break completely if they don't work correctly in the client, while others cause only minor issues in tooltips.