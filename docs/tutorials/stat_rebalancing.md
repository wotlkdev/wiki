---
layout: default
title: Stat Rebalancing
nav_order: 1
---

# Stat Rebalancing

This is an introduction to manipulating stat values and calculations on AzerothCore for WoW version 3.3.5.

- We will cover a brief theory of how stat calculations work, what files and source code to edit, as well as a basic introduction to the kind of mathematical transformations involved.

- We will then go on and provide specific pointers to where common item and stat calculations can be modified in AzerothCore as of [revision 0773ed2](https://github.com/azerothcore/azerothcore-wotlk/commit/0773ed25aa60281b355f4dfc18df590906641a12). I will attempt to keep descriptions version-agnostic and broad enough that variations to the exact source layout can be navigated around, but only so far that this is realistically possible. Major rewrites of the stat system would render this section of the guide outdated, and readers should be aware of potential discrepancies when applying it to emulator versions far into the future.

- This guide was originally written as a commission, so it focuses mostly on aspects requested by that client, but should still work as a good introduction to the stat system as a whole.

The kind of stats we will be discussing involve: 

- Primary stats, such as strength, stamina and intellect
- Secondary stats, such as attack power and armor
- Combat/Percentage-based ratings, such as haste rating, defense rating, critical strike rating and so on
- Pet stats
- "Final" stats, such as hitpoints, mana, mana regeneration and damage reductions.

## Prerequisites

This guide assumes a basic knowledge of the following topics:

- Compiling the core
- Reading (mostly basic) C++ code
- Editing databases with a tool like HeidiSQL or MySQL Workbench
- Editing DBC files with an editor such as WDBX.

## Disclaimers

Many of the stat covered in this guide should work and apply predictably as described, granted the proper emulator version and input data is used. However, wow emulators are not perfect and especially anything relating to spells has a tendency to contain specific _hardcodes_ in wildly different places around the core, causing unexpected behavior for specific items or spells. This guide does not include many pointers for navigating such hardcodes, but is better covered in a separate tutorial altogether. It is not possible to provide a comprehensive map to every such individual hardcode, there are simply too many of them.

This guide also does not include any pointers for manipulating spell data modifiers to stat calculations, and is better covered in a tutorial about spell creation and manipulation. However, if navigating source code around locations given in this tutorial, it is often possible to find and apply simpler transformations even to spell input for some stat types, usually via calls to `GetModifierValue` and similar functions. Keep in mind potential spell hardcodes if you decide to attempt this.

## Theory

This section includes introductions to the basic concepts we will be discussing in future sections, such as what kind of files may need to be edited, what kind of stats exist in the game, and what kind of mathematical transformations we can apply to them.

### Types of Stats

The stats we will discuss here all have various different mathematical traits and are defined in various ways throughout the game. 

#### Explicit Values

These are values in the game that are explicitly saved to the player, such as their experience, race or class. These values do not depend on any other type of value, but serve as "pure inputs" to other calculations.

#### Data Tables

These are values that depend on other values via some kind of lookup, typically lookups from explicit values, and most often the players level.

For example, players primary stats (without items/spells) depend on explicit lookups into the `player_levelstats` server database table, where a players race, class and level directly correlate to values for primary stats. In mathematical expressions for this guide, I will use the square bracket syntax for these types of lookups: `base_stats[class,race,level]`, reading "base_stats, depending on the players class, race and level".

#### Hidden / Shared Tables

Not all data tables correspond to a visible final stat in the game. In this guide, I will refer to these as "hidden tables". These tables are very important to keep in mind, as they often influence wildly different stats and can cause very unexpected behavior if edited carelessly, but often serve a very important role in how the players level affects their final stats. Examples of hidden data tables include DBC tables starting with `Gt`, as well as many hardcoded ratings coefficients found around the cores source code, in particular `StatSystem.cpp`.

#### Intermediate and "Final" Stats

These are values that depend on other stats in some way, usually involving multiplication, addition or other mathematical transformations. These stats make up the bulk of visible stats in the game, and can both be affected by and affect other stats directly.

For example, players level is technically an intermediate stat depending on their total experience, but is also used as a lookup in many different data tables and calculations on their own.

Other values, such as a players max hp, is typically understood to be a "final" stat that do not influence any other stats in the game. This is almost always incorrect, and stats thought to be "final" are almost always intermediate. Players max hp influence plenty of spells and scripts in the game. 

It is very important to remember that any stat you change in the game can have unexpected consequences for spell effects and scripts, both generic and hard-coded. In this guide, I will not be referring to any stat as final, but instead as "visible".

### Maths

Stat calculations in WoW can be complicated and involve a lot of variables and maths. This section will aim to explain in simple terms where and how you can often best achieve predictable results without necessarily understanding the full formula.

Specifically, we will look at **where** we often want to manipulate stat values, and what **kind** of transformations we want to apply to them.

#### Inputs and Outputs

As an example, let's look at how players max hp is calculated in the core as a function of their stamina, class, level and aura bonues:

```c++

// Mathematical definition: 
// MAX_HEALTH() =  ((player_classlevelstats[class,level] + base_unit_value) * BASE_PCT_MODIFIERS) + (max(stamina,20) + (stamina-max(stamina,20)*10 )) * TOTAL_VALUE_MODIFIERS) * TOTAL_PCT_MODIFIERS`

void Player::UpdateMaxHealth()
{
    UnitMods unitMod = UNIT_MOD_HEALTH;

    float value = 
          // base_unit_value
          GetModifierValue(unitMod, BASE_VALUE)
          // player_classlevelstats[class,level]
        + GetCreateHealth();

    // spells: base hp percentage
    value *= GetModifierValue(unitMod, BASE_PCT);

    // stamina, (after base spell pct, before total pct)
    value += GetHealthBonusFromStamina();

    // spells: flat spell modifier (after base spell pct, before total pct)
    value += GetModifierValue(unitMod, TOTAL_VALUE) 

    // spells: total hp percentage modifier
    value *= GetModifierValue(unitMod, TOTAL_PCT);

    // custom scripts, may apply additional changes
    sScriptMgr->OnAfterUpdateMaxHealth(this, value);

    // writes the value, not part of calculation
    SetMaxHealth((uint32)value);
}

...

float Player::GetHealthBonusFromStamina()
{
    // How much stamina the player is assumed to have for this calculation
    float stamina = GetStat(STAT_STAMINA);

    float baseStam = stamina < 20 ? stamina : 20;
    float moreStam = stamina - baseStam;

    // Base stamina contribution to hp before modifiers apply.
    return baseStam + (moreStam * 10.0f);
}
```

As you can see, there are **many** places where we can manipulate this formula, but I want to bring to your attention a few important places:

- Inputs: where we directly read another stat value, such as the line `float stamina = GetStat(STAT_STAMINA);`

- Outputs: where a stat directly contributes to the total value, such as the line `return baseStam + (moreStam * 10.0f);`

It is usually advisable to apply transformations close either to a calculations inputs or its outputs. The middle parts may contain very intricate logic that are not always very intuitive, and have often been developed out of necessity to balance the game or handle edge cases (such as the checks for very low stamina values above).

We can usually achieve more powerful expressions by applying transformations close to the **input** of a calculation, but this also means that it tends to cause changes to behave more unpredictably than if we apply it close to the **output**.

**In Summary**
- We usually want to apply transformations close to a functions inputs or its outputs
- Input transformations are more powerful but less stable than output transformations

#### Transformations

In mathematics, a transformation is simply a way that we take one value and _transform_ it into a another value. Common ways to transform stat values is to **add** and **multiply** them, but more complex transformations such as **polynomials**, **exponentials** and **logarithmics** are also possible. 

Polynomials and exponentials in particular are crucial to understand how **progression** in WoW works, and they show up very frequently in level-based data tables such as experience per level, spell damage, primary stats and gold rewards. However, inside calculations we usually stick to additions and multiplications, as more exotic transformations are usually so unpredictable that they rarely change the game in a useful way. A common way to express these in wow is "bonuses" for additions, and "multipliers/percentages/scalars" for multiplication.

**In Summary**
- Data tables tend to contain polynomial and exponential curves
- Calculations usually consist of addition (bonuses) and multiplication (multipliers/percentages/scalars) of values

#### Example: Stamina Transformation

Let's illustrate the above points by applying multiplication to the amount of stamina assumed when calculating players max health.

In particular, let's look at two deceptively similar statements:

- Double the amount of stamina used for calculating max health
- Double the amount of max health gained from stamina

At first glance, these statements might look equivalent, we double the stamina variable somewhere and it will "double" whatever we think of as the "output". However, because the stamina function contains logical comparisons and additions, these are **not equivalent**, and where exactly we double the "stamina" value matters. In mathematical terms, we say that the stamina expression is [non-commutative](https://en.wikipedia.org/wiki/Commutative_property).

##### Statement 1
```c++
float Player::GetHealthBonusFromStamina()
{
    // "Double the amount of stamina used for calculating max health"
    float stamina = GetStat(STAT_STAMINA) * 2; 
    float baseStam = stamina < 20 ? stamina : 20;
    float moreStam = stamina - baseStam;
    return baseStam + (moreStam * 10.0f);
}
```

##### Statement 2
```c++
float Player::GetHealthBonusFromStamina()
{
    float stamina = GetStat(STAT_STAMINA); 
    float baseStam = stamina < 20 ? stamina : 20;
    float moreStam = stamina - baseStam;
    // "Double the amount of health gained from stamina"
    return (baseStam + (moreStam * 10.0f)) * 2;
}
```

Exercise: Attempt to run a few different stamina values into these two functions and observe the output. In particular, try out stamina values both below and above 20.

**In Summary**
- Changing stat calculations is a very delicate process, and it's very important to analyze what exactly your transformations express.

## Data sources

This sections aims to lay out the different data sources that need to be taken into account when re-balancing the game.

### The "Hidden" DBC Tables (Gt*)

DBC tables with the prefix `gt` serve an important role in how many level-based calculations take place in the game, but because many don't have any direct visible equivalent, they are often unknown to many players and even some developers. 

These files contain important _percentage_ data for various calculations based on players levels and/or class. Contrary to many other data tables, these tables do not contain any columns indicating what level or class they actually map to, instead this is inferred from their index/id.

There are four types of `gt` DBC tables with different layouts:

#### Class Indices

These tables have only a single value per class. The first row is for warriors (class id 1), the second for paladins (class id 2), the third row for hunters (class id 3) and so on.

- `GtChanceToMeleeCritBase.dbc` (base melee crit ratios)
- `GtChanceToSpellCritBase.dbc` (base spell crit ratios)

#### Class / Level Indices

These tables contain 100 values per class, going from level 1 to level 100. The first 100 rows correspond to warriors, the following 100 rows to paladins and so on.

- `GtChanceToMeleeCrit.dbc` (level-based melee crit ratios)
- `GtChanceToSpellCrit.dbc` (level-based spell crit ratios)
- `GtOCTRegenHP.dbc` (non-spirit based hp regeneration)
- `GtOCTRegenMP.dbc` (non-spirit based mana regeneration)
- `GtRegenHPPerSpt.dbc` (spirit-based hp regeneration)
- `GtRegenMPPerSpt.dbc` (spirit-based hp regeneration)

#### Combat Rating/Level Indices

These tables contain 100 level values for 32 different combat ratings. Note that these values are **not** indexed by class, instead the first 100 rows correspond to `CR_WEAPON_SKILL` combat rating from level 1 to 100 for **all** classes, the following 100 rows to `CR_DEFENSE_SKILL` and so on.

The full list of combat rating types is as follows:

```c++
enum CombatRating
{
    CR_WEAPON_SKILL             = 0,
    CR_DEFENSE_SKILL            = 1,
    CR_DODGE                    = 2,
    CR_PARRY                    = 3,
    CR_BLOCK                    = 4,
    CR_HIT_MELEE                = 5,
    CR_HIT_RANGED               = 6,
    CR_HIT_SPELL                = 7,
    CR_CRIT_MELEE               = 8,
    CR_CRIT_RANGED              = 9,
    CR_CRIT_SPELL               = 10,
    CR_HIT_TAKEN_MELEE          = 11,
    CR_HIT_TAKEN_RANGED         = 12,
    CR_HIT_TAKEN_SPELL          = 13,
    CR_CRIT_TAKEN_MELEE         = 14,
    CR_CRIT_TAKEN_RANGED        = 15,
    CR_CRIT_TAKEN_SPELL         = 16,
    CR_HASTE_MELEE              = 17,
    CR_HASTE_RANGED             = 18,
    CR_HASTE_SPELL              = 19,
    CR_WEAPON_SKILL_MAINHAND    = 20,
    CR_WEAPON_SKILL_OFFHAND     = 21,
    CR_WEAPON_SKILL_RANGED      = 22,
    CR_EXPERTISE                = 23,
    CR_ARMOR_PENETRATION        = 24
};
```

Note that out of the 32 possible tables, only 25 are actually used by the game and the rest were probably left in for future use. 32 is a nice round number if you happen to count in binary.

#### Combat Ratings / Class Indices

This is another special table that concern combat ratings, but instead of being indexed by level they are indexed by class and contain 32 values per class. The first 32 rows correspond to warriors, the following 32 rows to paladins and so on. In any given 32 row chunk, the first row corresponds to `CR_WEAPON_SKILL`, the second row to `CR_DEFENSE_SKILL` and so on.

**In Summary**
- Gt tables contain important percentage data for different calculations, and are especially important when re-balancing calculations based on levels or classes.
- For most intents, it's probably enough to know these tables exist and where such level/class-based ratios come from.

_Exercise 1: If you open the file gtRegenHPPerSept.dbc in WDBX, you may notice that ids between 901 and 1000 are just 0. Why do you think this is? (hint: try looking at the class table in `ChrClasses.dbc`)_

_Exercise 2: `Gt` tables are the cause for the infamous crashes that druids experience on levels above 100, since they only contain 100 values per class. Druids, having the highest class id in the game, causes the character frame to almost always read uninitialized memory and crash the game if you open it. Knowing this, what kind of values do you think are displayed if you level up a mage to 101?_

### Server Database Tables

Non-percentage data is stored in tables in the servers mysql database. These tables contains players base hp/mana and primary stats depending on their level, class, and/or race.

- `player_xp_for_level`: How much experience is needed for each level
- `player_levelstats`: Primary stats for each level depending on race and class
- `player_classlevelstats`: Base hp/mana for each level depending on class.

### Hardcoded Source Tables

A few data tables are (for some reason) hardcoded into `StatSystem.cpp`, but these might move into database tables one day. These tables contain class-specific ratios that don't correspond to anything very intuitive, and their use is very local to the functions and file they are defined in.

These values typically refers to "diminishing" and "cap" values, but should not be confused with the common in-game "item caps" usually going by the same name, though these values do influence such caps even if indirectly.

_note: if these tables change name, you can likely still find them by searching the files for the "[MAX_CLASSES]" array size specifier._

- `m_diminishing_k` - diminishing ratios for multiple percentage calculations
- `miss_cap` - caps for diminishing miss values
- `parry_cap` - caps for diminishing parry values
- `dodge_cap` - caps for diminishing dodge values

## Reading Source Code

In this section, we will look closer at how these values are actually handled by the emulator core, as well as some pointers for how to do future research and how they are found.

### Learning Source Code

When navigating C++, a proper IDE is invaluable to find things you are looking for. If you are not editing files directly, modern versions of Visual Studio work very well to easily click on identifiers to find their declarations and definitions.

Knowing well what things to search for is also important, because not all values can be found just by following references around.

For example, say that we want to find calculations relating to expertise. This is a combat rating that uses the enum value `CR_EXPERTISE`, and if we search the entire core repository for this string we can see that it shows up in only a few source files. This gives us functions such as `Player::_ApplyItemMods`, `Player::ApplyEnchantment`, `Player::UpdateRating`, `Player::UpdateExpertise` to investigate. This might seem overwhelming already, but remember that most stats in the game work very similarly to other stats similar to itself, so if we just start reading functions one by one we will eventually build familiarty with the system as we eventually reach a point of re-visiting the same functions over and over again.

It is important to remember that not every function will do exactly what it is we're trying to get it to do, and sometimes their names are deceptive. If investigating source code on your own, it is important to work carefully and analyze what the current function is actually doing. Many values in WoW emulators are cached whenever something that influence them changes, and very few values are ever calculated straight from all its sources directly. This can cause many calculations to be disjointed, and it is usually necessary to search further for such cached data if you encounter it.

**In Summary**
- Searching and following references are fundamental building blocks for learning to navigate source code.
- Searching for enum values is a highly effective way to find stat calculations
- WoW emulators cache many of its values, so many calculations are disjointed.

### Update Data

Update data refers to a big block of special fields stored on different game entities, such as creatures and players, meant to be sent to clients when they change. Any time you see source code that reads `entity->SetUInt32Value`, `entity->SetFloatValue`, `entity->GetUInt32Value` and so on, this refers to updatedata fields.

These fields are very important in many stat calculations, as they are both used to send stat data to the client and to cache values when stat inputs change. A very common pattern for stat updates is that one functions write to an updatedata field that another function reads shortly after.

All update fields for different object types can be found in `UpdateFields.h`, and especially interesting for stat re-balancing are `Unit` and `Player` fields.

There is little point in studying these fields on their own, and their purpose can be deceptive out of context, but it is important to be aware of what they are if you do encounter them. Many times stat calculations do not call `SetXValue` functions directly, but via some wrapper function, some of which we will encounter in the following sections.

It is also important to be aware that some update data fields can contain multiple values inside a single field. For example, `PLAYER_FIELD_COMBAT_RATING_1` has a size of 25, and contains separate values for each combat rating type.

### Entry points

Following are some general starting points for reading about stat-related calculations specifically, some files and some functions. These will feature heavily in the following sections.

- `StatSystem.cpp` - Probably the most important file for stat calculations.
- `Player.cpp` - Contains some offshoots from `StatSystem.cpp`
- `SharedDefines.h` - Contains most stat-related enums
- `Player::ApplyRatingMod`
- `Player::ApplyEnchantment`
- `Player::_ApplyItemBonuses`

Pet calculations
- `Pet.cpp`

## Stat Transformations

This sections contain a long list of specific stat transformation examples that can serve as an introduction to the stat system.

In this section, I will commonly use a convention of pointing out what **Function** a value is supposed to be changed in, as well as what **Expression** is supposed to be transformed for the desired effect.

For example, if we had the following (example) function:

```c++
void MyClass::GetHealthFromStamina()
{
    int val1 = GetStat(STAT_STAMINA);
    if(val1 < 20) val1 = 20;
    return val1 * 10;
}
```

I might describe transforming "the amount of stamina used for calculating max health" as follows:

- **Function**: `MyClass::GetHealthFromStamina`

- **Expression**: `GetStat(STAT_STAMINA)`

Meaning, in plain english, that to apply the desired transformation, you should find the function called `MyClass::GetHealthFromStamina`, and within it you should find and transform the expression `GetStat(STAT_STAMINA)`. For example, if you wanted to double the amount of stamina used for calculating the maximum health, you would change this function to:

```c++
void MyClass::GetHealthFromStamina()
{
    int val1 = (GetStat(STAT_STAMINA) * 2);
    if(val1 < 20) val1 = 20;
    return val1 * 10;
}
```

For some calculations, there may be multiple such expressions you need to change, and this will be expressed in the notation if so. For other calculations, the process of transforming it is more complicated and contains a more verbose description of how to achieve the desired effect.

### Primary Stats

Primary stats refer to the typical rpg stats strength, agility, intellect, spirit and stamina.

When working with primary stats, you will commonly encounter constants from the `Stats` enum, defined in `SharedDefines.h`. Its members have the prefix `STAT_`, so whenever you stumble upon identifiers like `STAT_STRENGTH`, they refer to this enum.

Commonly, primary stat values are read with the Player method `GetStat(StatType)`, such as `GetStat(STAT_STRENGTH)`. This function returns the effective value of this stat on the player with spell modifiers applied.

#### Agility -> Armor

- **Function**: `Player::UpdateArmor`

- **Expression**: `GetStat(STAT_AGILITY)`

- **Example**: Adding a flat +20 bonus to agility used for armor
    ```c++
    void Player::UpdateArmor()
        ...
        value *= GetModifierValue(unitMod, BASE_PCT);           // armor percent from items
        value += (GetStat(STAT_AGILITY) + 20) * 2.0f;           // armor bonus from stats
        value += GetModifierValue(unitMod, TOTAL_VALUE);
        ...
    ```

#### Agility / Strength -> Attack Power

**This transformation is complex, and requires reading source code**

- **Function**: `Player::UpdateAttackPowerAndDamage`

- **Expression**: Any instance of `GetStat(STAT_AGILITY)` and `GetStat(STAT_STRENGTH)` respectively.

- **Note**: This function is divided into ranged/non-ranged attack power and switches between each individual class. Individual formulas are relatively straight forward, but because of the combinatorics the function is relatively complex. Druids in particular have some nasty hardcodes here, so changing their formulas requires some reading.

- **Note**: If you wish to apply generic transformations to the calculated attack power in this function, you can track the `val2` variable and write to it before the first call to `SetModifierValue(...)`

#### Armor -> Damage Reduction

- **Function**: `Unit::CalcArmorReducedDamage`

- **Expression**: Look for the statement `float armor = float(victim->GetArmor());` and transform the `victim->GetArmor()` part

- **Note**: Armor is further modified inside the `if(attacker)` for things like armor penetration and ignore auras.

- **Note**: Post-modifier armor is below the `if (armor < 0.0f) armor = 0;` check, and is applied to damage through a final formula below it. Note that this function cannot normally return values below 1.

#### Block Value -> Blocked Damage

- **Function**: `Unit::CalculateMeleeDamage`

- **Expression**:  In the switch case for `MELEE_HIT_BLOCK`, after statement `damageInfo->blocked_amount = damageInfo->target->GetShieldBlockValue();`, the expression  `damageInfo->blocked_amount` contains the effective shield block value, which also factors in things like strength stat.

- **Note**: If you wish to only affect shield block value itself without the strength stat factored in, you need to dissect `Player::GetShieldBlockValue` because it is called by multiple other functions in the core, including one that writes to update data.

#### Agility -> Critical Hit

**Despite its name, this function is used for both melee and ranged critical hit ratings**

- **Function**: `Player::GetMeleeCritFromAgility`

- **Expression**: `GetStat(STAT_AGILITY)`

- **Further reading**: `Player::UpdateAllCritPercentages`

#### Stamina -> Max Health

- **Function**: `Player::GetHealthBonusFromStamina`

- **Expression**: `GetStat(STAT_STAMINA)`

- **Further reading**: `Player::UpdateMaxHealth` for base data and other modifiers.

#### Intellect -> Max Mana

- **Function**: `Player::GetManaBonusFromIntellect`

- **Expression**: `GetStat(STAT_INTELLECT)`

- **Further reading**: `Player::UpdateMaxPower` for base data and other modifiers.

#### Intellect -> Spell Crit

- **Function**: `Player::GetSpellCritFromIntellect`

- **Expression**: `GetStat(STAT_INTELLECT)`

- **Further Reading**: `Player::UpdateSpellCritChance`

#### Spirit -> Mana Regen

- **Function**: `Player::OCTRegenMPPerSpirit`

- **Expression**: `GetStat(STAT_SPIRIT)`

#### Intellect -> Mana Regen

- **Function**: `Player::UpdateManaRegen`

- **Expression**: `GetStat(STAT_INTELLECT)`

#### Cast State Mana Regen

**This transformation is complex, and requires reading source code**

- **Function**: `Player::UpdateManaRegen`

- **Expression**: At the bottom of these functions, two update data fields are written:
  - `UNIT_FIELD_POWER_REGEN_INTERRUPTED_FLAT_MODIFIER` - In-combat mana regen regeneration
  - `UNIT_FIELD_POWER_REGEN_FLAT_MODIFIER` - Out-of-combat mana regeneration

  Either value can be transformed or swapped before writing to change their relationship.

### Secondary Stats

Secondary stats, in this guide, refer to non-combat rating stats like attack power.

#### Attack Power

**This transformation is complex, and requires reading source code**

Attack power used for virtually all damage calculations is calculated in `Unit::GetTotalAttackPowerValue`. Transforming any returned value here will transform effective attack power for virtually any calculation in the game. It is also possible to transform this value as used by individual calculations by simply searching the entire source for `GetTotalAttackPowerValue` and transforming the function call expression.

- **Side-Effects**: `Unit::GetTotalAttackPowerValue` is also read in `LFGMgr` power calculations, so transforming it might break LFG calculations if not compensated for.

### Combat Ratings

As we've seen in the above sections, combat ratings are values that tends to calculate into a **percentage** value of some kind. These include stats such as hit rating, haste rating, critical strike rating and defense rating.

Combat ratings are defined in the `CombatRating` struct in `Unit.h`, and its members all contain the `CR_` prefix. If you see an all-uppercase identifier starting with `CR_`, it is typically a reference to this enum:

```c++
enum CombatRating
{
    CR_WEAPON_SKILL             = 0,
    CR_DEFENSE_SKILL            = 1,
    CR_DODGE                    = 2,
    CR_PARRY                    = 3,
    CR_BLOCK                    = 4,
    CR_HIT_MELEE                = 5,
    CR_HIT_RANGED               = 6,
    CR_HIT_SPELL                = 7,
    CR_CRIT_MELEE               = 8,
    CR_CRIT_RANGED              = 9,
    CR_CRIT_SPELL               = 10,
    CR_HIT_TAKEN_MELEE          = 11,
    CR_HIT_TAKEN_RANGED         = 12,
    CR_HIT_TAKEN_SPELL          = 13,
    CR_CRIT_TAKEN_MELEE         = 14,
    CR_CRIT_TAKEN_RANGED        = 15,
    CR_CRIT_TAKEN_SPELL         = 16,
    CR_HASTE_MELEE              = 17,
    CR_HASTE_RANGED             = 18,
    CR_HASTE_SPELL              = 19,
    CR_WEAPON_SKILL_MAINHAND    = 20,
    CR_WEAPON_SKILL_OFFHAND     = 21,
    CR_WEAPON_SKILL_RANGED      = 22,
    CR_EXPERTISE                = 23,
    CR_ARMOR_PENETRATION        = 24
};
```

Combat ratings are among the more complex stats in the game, and transforming them requires understanding the different steps at which they are applied, where their bonuses come from and how the core itself transforms them. There is no simple way to transform "a players flat combat rating" into almost any bonus.

#### Generic Combat Rating Storage and Functions

**This transformation is complex, and requires reading source code**

Combat rating data is stored in a few distinct fields on players, and these change whenever players equip/unequip items or gains/loses auras that modify them:

- `Player::m_baseRatingValue` - contains a raw tally of all combat rating stats gained from items without any modifiers applied. Haste ratings read directly from this value when calculating their bonuses.

- Update data fields `PLAYER_FIELD_COMBAT_RATING_1` - contains combat stat points read from `Player::m_baseRatingValue` after spell modifiers have been applied. With the exception of haste ratings, this is what most combat rating calculations actually read.

There are also a few generic functions that keep showing up in combat rating calculations that are worth being aware of:

- `Player::GetRatingMultiplier` - This function reads `GtCombatRatings.dbc` and `GtOCTClassCombatRatingScalar.dbc` data into a single scalar modifier for the players level and stats. The input and out of this function can be transformed to manipulate the dbc stats without actually changing the underlying tables.

- `Player::GetRatingBonusValue` - This function reads the `PLAYER_FIELD_COMBAT_RATING_1` update data field and multiplies it by `Player::GetRatingMultiplier` for a specific combat rating. This is typically the function used whenever combat rating bonuses are applied around the core, and can be modified to apply generic modifiers from displayed combat ratings to effective combat rating values used in calculations. Keep in mind that not all combat ratings use this field, such as haste ratings.

  For example, if you wanted to apply a generic +10 bonus to all defense rating calculations for hunters you could change the function into something like this:

  ```c++
  float Player::GetRatingBonusValue(CombatRating cr) const
  {
    return float(GetUInt32Value(static_cast<uint16>(PLAYER_FIELD_COMBAT_RATING_1) + cr)) * GetRatingMultiplier(cr) + (cr == CR_DEFENSE_SKILL && getClass() == CLASS_HUNTER) ? 10 : 0;
  }
  ```

- `Player::ApplyRatingMod` - This function is called whenever a player changes their equipment so that a combat rating stat changes. The purpose of this function is to:
    1. Set raw combat rating data into `Player::m_baseRatingValue`
    2. Handle the three haste rating types raw from this value
    3. Call `Player::UpdateRating`

- `Player::UpdateRating` - This is the main function calculating effective combat rating values. It can be used for applying base combat rating data (`m_baseRatingValues`) into post-spell-modifier values (`PLAYER_FIELD_COMBAT_RATING_1`) stored in update data, and as a generic entrypoint into more specific target update data fields, particularly percentage-based ones.

#### Defense Rating

**This stat is complex, and requires reading source code to understand fully**

Defense rating is a combat rating that commonly acts both as a distinct value and as a modifier to the players defense skill.

An important function to be aware of for defense rating calculations is `Player::GetDefenseSkillValue`, which is used as a sort of generic modifier adding together the players defense skill and the combat rating bonus on top. It is called when calculating _most_ stats that are influenced by defense rating, but not all of them.

Modifying defense rating itself can be most easily done inside `Player::GetRatingBonusValue` with a specific check for defense rating, as **all** defense rating stats calls this function at some point, either directly or through `Player::GetDefenseSkillValue`. Just like with other combat ratings that depend on dbc data, this can be used both to transform the input base combat rating bonus and the output bonus with dbc data applied.

#### Defense -> Crit Percentages

- **Functions**: `Unit::GetUnitCriticalChance`, `Unit::SpellTakenCritChance` (both contain the same formula)

- **Expression**: Look for a line that contains `victim->GetDefenseSkillValue`. This line contains the full formula for how defense skill and rating affects crit. 

#### Defense -> Dodge/Parry Percentages

These two stats are calculated near identically, so we will cover them in a single section.

- **Functions**: `Player::UpdateDodgePercentage`, `Player::UpdateParryPercentage` for each stat respectiverly.

- **Expression**: Look for a call to `GetRatingBonusValue(CR_DEFENSE_SKILL)` - note how these are among the few combat rating stats that do not call `GetDefenseSkillValue` but instead reads the rating directly.

#### Defense -> Block Percentage

- **Function**: `Player::UpdateDodgePercentage`

- **Expression**: `Player::GetDefenseSkillValue()`

#### Dodge Rating -> Dodge Percentage

- **Function**: `Player::UpdateDodgePercentage`

- **Expression**: `GetRatingBonusValue(CR_DODGE)`

#### Parry Rating -> Parry Percentage

- **Function**: `Player::UpdateParryPercentage`

- **Expression**: `GetRatingBonusValue(CR_PARRY)`

#### Block Rating -> Block Percentage

- **Function**: `Player::UpdateBlockPercentage`

- **Expression**: `GetRatingBonusValue(CR_BLOCK)`

#### Haste Ratings -> Attack / Cast Time Percentages

- **Function**: `Player::ApplyRatingMod`

- **Expression**: Inside the check for haste ratings, transform `mult` before it is being read into any other variables (e.g. `oldVal`/`newVal`).

- **Notes**: This transformations has very strict rules and must not behave in such a way that can ever change for a single character (such as reading any other stats, randomness or character state). Things that can typically be used for this transformation include player class, race and the `CombatRating` enum itself.

#### Haste -> GCD Reduction

- **Function**: `Spell::TriggerGlobalCooldown`

- **Expression**: `m_caster->GetFloatValue(UNIT_MOD_CAST_SPEED))`

#### Haste -> Cast Time

- **Function**: `Unit::ModSpellCastTime`

- **Input**: All instances of `GetFloatValue(UNIT_MOD_CAST_SPEED)`

- **Further reading**: `SpellInfo::CalcCastTime`

#### Spell Crit

- **Expression**: `Unit::SpellDoneCritChance`

- **Input**: All instances of `GetFloatValue(...)` with enum values  `PLAYER_CRIT_PERCENTAGE`, `PLAYER_OFFHAND_CRIT_PERCENTAGE`, `PLAYER_RANGED_CRIT_PERCENTAGE`.

#### Resilience

**This transformation is complex, and requires reading source code**

Resilience is a type of combat rating written into the following three ratings identically:

- `CR_CRIT_TAKEN_MELEE`
- `CR_CRIT_TAKEN_RANGED`
- `CR_CRIT_TAKEN_SPELL`

**Despite their names**, these three rating values are used for **all** resilience calculations, including non-crit damage, and **the names are thus misleading**.

The most important function for reading resilience is `Unit::ApplyResilience`, and serves as the entrypoint to more specific calculations.

The way these functions work is somewhat convoluted and there is no easy way to explain how to change individual stats with a single transformation, rather the whole subsystem must be understood to know how to modify the individual functions to do what you want. There are two functions that must be understood at the bottom:

- `Unit::GetCombatRatingReduction(CombatRating)` - Returns the bonus value for a specific combat rating for a player or their pet.

- `Unit::GetCombatRatingDamageReduction(CombatRating,rate,cap,damage)` - Calculates a damage reduction for a specific combat rating (by calling `Unit::GetCombatRatingReduction`) and multiplying it by a `rate`, capping it off and returning a value between 0 and 1.

Now that we know these two functions, we can follow the outline of `Unit::ApplyResilience` to understand how different resilience reductions are calculated:

- `Unit::ApplyResilience`
  - `Unit::GetMeleeCritDamageReduction`
    - `Unit::GetCombatRatingDamageReduction`
  - `Unit::GetRangedCritDamageReduction`
    - `Unit::GetCombatRatingDamageReduction`
  - `Unit::GetSpellCritDamageReduction`
    - `Unit::GetCombatRatingDamageReduction`
  - `Unit::GetMeleeDamageReduction`
    - `Unit::GetCombatRatingDamageReduction`
  - `Unit::GetRangedDamageReduction`
    - `Unit::GetCombatRatingDamageReduction`
  - `Unit::GetSpellDamageReduction`
    - `Unit::GetCombatRatingDamageReduction`
  - `Unit::GetMeleeCritChanceReduction`
    - `Unit::GetCombatRatingReduction`
  - `Unit::GetRangedCritChanceReduction`
    - `Unit::GetCombatRatingReduction`
  - `Unit::GetSpellCritChanceReduction`
    - `Unit::GetCombatRatingReduction`

As you can see, because of the extensive use of these two generic functions they need to be extensively changed to allow transforming individual resilience values for individual damage types, since the type of reduction or critical hit status is not passed into them by default, and the resilience values themselves are so extensively transformed by them that their output have very little in common with it.

#### Expertise Rating

**This transformation is complex, and requires reading source code**

Expertise is stored as a normal combat rating value in update data, but also splits and writes into distinct update data fields `PLAYER_EXPERTISE` and `PLAYER_OFFHAND_EXPERTISE` in the function `Player::UpdateExpertise`

#### Expertise -> Dodge/Parry reduction

- **Function**: `Player::GetExpertiseDodgeOrParryReduction`

- **Expression**: Calls to `GetUInt32Value` for each weapon attack type respectively.

- **Note**: To separate calculations for either dodge or parry, search the entire source code for calls to `GetExpertiseDodgeOrParryReduction`, it should give you 4 results where the expression is clearly read into either a dodge or parry variable.

- **Further Reading**: `Unit::RollMeleeOutcomeAgainst`, `Unit::MeleeSpellHitResult`

#### Armor Penetration -> Armor Ignored

- **Function**: `Unit::CalcArmorReducedDamage`

- **Expression**: `attacker->ToPlayer()->GetRatingBonusValue(CR_ARMOR_PENETRATION)`

- **Note**: There is a cap for how much armor can be reduced calculated into the `maxArmorPen` variable right above the expression.

### Pet Stats

_Note: Emulators refer to player pets (both warlock-style and hunter pets) as "Guardians", which should not be confused with the engineering pets commonly called guardians in the game._

Pet stat handling is very complex and involves both database tables, hardcoded C++ values and pet-specific aura spells.

Generally, these are divided into:

- Base pet-specific stat data - Stored in the `pet_levelstats` database table

- Default pet stat data - Hardcoded into various places of `Pet.cpp`

- Pet-specific stat scalars - Hardcoded into various places of `Pet.cpp`

- Player to pet stat bonuses - Exclusively done using aura effects that are applied in various ways.

#### Pet Primary Stats

**This transformation is complex, and requires reading source code**

- Base stat data per level and pet is stored in the `pet_levelstats` database table.

- If no primary stats are found `pet_levelstats`, default values are found in `Guardian::InitStatsForLevel` (when not found in the above table), by searching for `SetCreateStat` and looking for a chunk that looks similar to this:

```c++
SetCreateStat(STAT_STRENGTH, 22 + 2 * petlevel);
SetCreateStat(STAT_AGILITY, 22 + 1.5f * petlevel);
SetCreateStat(STAT_STAMINA, 25 + 2 * petlevel);
SetCreateStat(STAT_INTELLECT, 28 + 2 * petlevel);
SetCreateStat(STAT_SPIRIT, 27 + 1.5f * petlevel);
```

#### Pet Attack Damage

- **Function**: `Guardian::InitStatsForLevel`

- **Expression**: Below the stat code there is a big switch statement on the petType like this: `switch (petType)`. In this statement individual "weapon" damage are set up and can be manipulated per pet type.

#### Pet Strength/Agility -> Attack Power

- **Function**: `Guardian::UpdateAttackPowerAndDamage`

- **Expression**: calls to `GetStat` with enums like `STAT_STRENGTH` and `STAT_AGILITY` throughout the function.

#### Pet Happiness -> Damage

- **Function**: `Guardian::UpdateDamagePhysical`

- **Expression**: Near bottom of the function is a switch statement over the different happiness states.

#### Pet Agility -> Armor

- **Function**: `Guardian::UpdateArmor`

- **Expression**: `GetStat(STAT_AGILITY)`

#### Pet Stamina -> Max Health

- **Function**: `Guardian::UpdateMaxHealth`

- **Expression**: `GetStat(STAT_STAMINA)`

- **Note**: In the middle of the function are various other pet-specific transformations applied.

#### Pet Intellect -> Max Mana

- **Function**: `Guardian::UpdateMaxPower`

- **Where**:
    - Effective intellect: `GetStat(STAT_INTELLECT)`
    - Base intellect: `GetCreateStat(STAT_INTELLECT)`

- **Note**: Pet-specific transformations in the middle of the function

#### Player Stats -> Pet Stats

**This transformation is very complex and requires reading source code in multiple files as well as DBC tools**

Player -> Pet stats are generally handled by pet-specific aura effects for both primary and secondary stats. For this reason, this is probably one of the most complicated transformations that can be done, and knowledge of reading spell effect handlers is necessary.

##### Finding Pet Stat Scaling Auras

There is no documentation for exactly what spell auras are used for what pets, however there are three common methods to find them:

- Many of these auras have the spell name `Tamed Pet Passive (DND)`, and often contain an icon indicating what pet they are for.

- Many auras are applied through CreatureFamily entries. The connection works as follows:
  - Entries in `creature_template` contains a field "family" that references an entry in `CreatureFamily.dbc`
  - Entries in `CreatureFamily.dbc` contain two skilline fields, `SkillLine_1` and `SkillLine_2`
  - Entries in `SkillLineAbility.dbc` contains fields referencing a spell from `Spell.dbc`, as well as a SkillLine from `SkillLine.dbc`
  - An aura spell is automatically applied to a pet if it meets the following requirements:
    - The spell is a passive aura
    - The spell has no spell level set
    - The spell has an ability with acquire method set to 2
    - One of the two skilline fields in the pets creature family entry matches the above abilitys skilline.
  - This happens in `LoadDBCStores` function in `DBCStores.cpp`, specifically the part looping over `CreatureFamilyEntry` values

- Other auras not covered by pet family entries are applied manually to different pet types inside `Guardian::InitStatsForLevel` inside the big `petType` switch statement with calls to `AddAura`

##### Reading Hardcoded Scripts

Much of pet scaling uses the scaling auras mentioned above, but generally goes through custom scripts for classes like hunter or warlock. Manipulating these often come down to finding the matching function handling them inside the class script files and looking for the individual spell ids.

1. Figure out what spell you are modifying, either by inspecting the pets active auras or the methods mentioned above.

2. Find your class script file. These are located in `src\server\scripts\Spells/spell_yourclass.cpp`

3. For most classes there is a dedicated function handling most scaling, usually found by searching for `scaling`.

4. Read the code. Pet scaling is so hardcoded that there isn't much else to do, usually with specific formulas for specific pets under specific classes.

##### Reading Spell Aura Effects

Most of the aura effects are properly implemented in the actual spell effects in dbc, but for some of them it is necessary to be able to read spell effect handlers to handle hardcodes. This section will briefly explain how to go from an aura effect in DBC to an effect handler in the core.

1. Find your aura effect. This can be done with a DBC editor like WDBX or the Spell Editor, I would recommend the latter as it includes spell aura names. For this example, let's assume we find the spell aura `SPELL_AURA_MOD_TOTAL_STAT_PERCENTAGE`.

2. Find the aura effect handler. This is commonly done by searching for `SPELL_AURA_MOD_TOTAL_STAT_PERCENTAGE` inside `SpellAuraEffects.cpp`. This will give you a line similar to `&AuraEffect::HandleModTotalPercentStat,                       //137 SPELL_AURA_MOD_TOTAL_STAT_PERCENTAGE`, and the function pointer on this line is your aura effect handler.
    - Alternatively, if you only have the numeric aura id, you can usually search for `//aura-id` (`//137` in this case) to find the same line.

3. Read the effect handler. Either search for the effect handler function or shift-click it in Visual Studio to go to the implementation. The contents here are completely dependent on the aura effect and needs to be read in their entirety to be understood.


### Threat

Threat is a relatively simple and generic calculation in the game. Whenever a unit deals damage or casts a spell they generate threat to the target or nearby enemies, and the player with the most threat (save for taunts) is the one that creatures attacks.

The interesting files and tables for threat are:

- `ThreatMgr.cpp` / `ThreatMgr.h`
- `Unit.cpp` / `Unit.h`
- `Spell.dbc` (for threat-related effects)
- `spell_threat` world table

#### Spell Threat (database)

- **World Table**: `spell_threat`

- **Note**: This table is perfect for arbitrarily modifying threat generated by spells on a per-spell basis

#### Threat -> Threat (core)

- **Function**: `ThreatCalcHelper::calcThreat`

- **Expression**: the `threat` variable anywhere in this function. Early is before spell modifiers, late is after spell modifiers.

- **Note**: If you want to apply a transformation _after_ school-specific modifiers, you can follow the tail call to `hatedUnit->ApplyTotalThreatModifier` and do your transform in that function as well.

- **Further Reading**: `Unit::AddThreat`, `ThreatMgr::addThreat`

#### Taunts

- **Function**: `Unit::TauntApply`, `Unit::TauntFadeOut`

- **Note**: These are the functions that ultimately handles taunts on AzerothCore. As of the commit this article is written for, you can also see that the ThreatMgrs taunt handling is commented out and completely unused.