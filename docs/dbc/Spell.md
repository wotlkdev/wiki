---
layout: default
title: Spell
nav_exclude: true
---
# Spell
This table is where all the spells in the game are defined, aside from a small amount of server-only spells that are sometimes stored in the cores `spell_dbc` table.


| Column | Type | Reference | Comment |
|--------|------|-----------|---------|
|ID|int32|||
|Category|int32|[SpellCategory#ID](SpellCategory)||
|DispelType|int32|[SpellDispelType#ID](SpellDispelType)||
|Mechanic|int32|[SpellMechanic#ID](SpellMechanic)||
|Attributes|int32|||
|AttributesEx|int32|| See [AttributesEx](https://wowdev.wiki/Spell.dbc/AttributesEx)|
|AttributesExB|int32|| See [AttributesExB](https://wowdev.wiki/Spell.dbc/AttributesExB)|
|AttributesExC|int32|| See [AttributesExC](https://wowdev.wiki/Spell.dbc/AttributesExC)|
|AttributesExD|int32|| See [AttributesExD](https://wowdev.wiki/Spell.dbc/AttributesExD)|
|AttributesExE|int32|| See [AttributesExE](https://wowdev.wiki/Spell.dbc/AttributesExE)|
|AttributesExF|int32|| See [AttributesExF](https://wowdev.wiki/Spell.dbc/AttributesExF)|
|AttributesExG|int32|| See [AttributesExG](https://wowdev.wiki/Spell.dbc/AttributesExG)|
|ShapeshiftMask|int32[2]|||
|ShapeshiftExclude|int32[2]|||
|Targets|int32|||
|TargetCreatureType|int32|||
|RequiresSpellFocus|int32|[SpellFocusObject#ID](SpellFocusObject)||
|FacingCasterFlags|int32|||
|CasterAuraState|int32|||
|TargetAuraState|int32|||
|ExcludeCasterAuraState|int32|||
|ExcludeTargetAuraState|int32|||
|CasterAuraSpell|int32|||
|TargetAuraSpell|int32|||
|ExcludeCasterAuraSpell|int32|||
|ExcludeTargetAuraSpell|int32|||
|CastingTimeIndex|int32|[SpellCastTimes#ID](SpellCastTimes)||
|RecoveryTime|int32|||
|CategoryRecoveryTime|int32|||
|InterruptFlags|int32|||
|AuraInterruptFlags|int32|||
|ChannelInterruptFlags|int32|||
|ProcTypeMask|int32|||
|ProcChance|int32|||
|ProcCharges|int32|||
|MaxLevel|int32|||
|BaseLevel|int32|||
|SpellLevel|int32|||
|DurationIndex|int32|[SpellDuration#ID](SpellDuration)||
|PowerType|int32|||
|ManaCost|int32|||
|ManaCostPerLevel|int32|||
|ManaPerSecond|int32|||
|ManaPerSecondPerLevel|int32|||
|RangeIndex|int32|||
|Speed|float|||
|ModalNextSpell|int32|||
|CumulativeAura|int32|||
|Totem|int32[2]|||
|Reagent|int32[8]|[Item#ID](Item)||
|ReagentCount|int32[8]|||
|EquippedItemClass|int32|||
|EquippedItemSubclass|int32|||
|EquippedItemInvTypes|int32|||
|Effect|int32[3]|||
|EffectDieSides|int32[3]|||
|EffectRealPointsPerLevel|float[3]|||
|EffectBasePoints|int32[3]|||
|EffectMechanic|int32[3]|[SpellMechanic#ID](SpellMechanic)||
|ImplicitTargetA|int32[3]|||
|ImplicitTargetB|int32[3]|||
|EffectRadiusIndex|int32[3]|[SpellRadius#ID](SpellRadius)||
|EffectAura|int32[3]|||
|EffectAuraPeriod|int32[3]|||
|EffectAmplitude|float[3]|||
|EffectChainTargets|int32[3]|||
|EffectItemType|int32[3]|||
|EffectMiscValue|int32[3]|||
|EffectMiscValueB|int32[3]|||
|EffectTriggerSpell|int32[3]|[Spell#ID](Spell)||
|EffectPointsPerCombo|float[3]|||
|EffectSpellClassMaskA|int32[3]|||
|EffectSpellClassMaskB|int32[3]|||
|EffectSpellClassMaskC|int32[3]|||
|SpellVisualID|int32[2]|[SpellVisual#ID](SpellVisual)||
|SpellIconID|int32|[SpellIcon#ID](SpellIcon)||
|ActiveIconID|int32|[SpellIcon#ID](SpellIcon)||
|SpellPriority|int32|||
|Name_lang|locstring|||
|NameSubtext_lang|locstring|||
|Description_lang|locstring|||
|AuraDescription_lang|locstring|||
|ManaCostPct|int32|||
|StartRecoveryCategory|int32|||
|StartRecoveryTime|int32|||
|MaxTargetLevel|int32|||
|SpellClassSet|int32|||
|SpellClassMask|int32[3]|||
|MaxTargets|int32|||
|DefenseType|int32|||
|PreventionType|int32|||
|StanceBarOrder|int32|||
|EffectChainAmplitude|float[3]|||
|MinFactionID|int32|[Faction#ID](Faction)||
|MinReputation|int32|||
|RequiredAuraVision|int32|||
|RequiredTotemCategoryID|int32[2]|[TotemCategory#ID](TotemCategory)||
|RequiredAreasID|int32|[AreaGroup#ID](AreaGroup)||
|SchoolMask|int32|||
|RuneCostID|int32|[SpellRuneCost#ID](SpellRuneCost)||
|SpellMissileID|int32|[SpellMissile#ID](SpellMissile)||
|PowerDisplayID|int32|[PowerDisplay#ID](PowerDisplay)||
|EffectBonusCoefficient|float[3]|||
|DescriptionVariablesID|int32|[SpellDescriptionVariables#ID](SpellDescriptionVariables)||
|Difficulty|int32|||
