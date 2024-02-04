---
layout: default
title: CreatureSoundData
nav_exclude: true
---
# CreatureSoundData

| Column | Type | Reference | Comment |
|--------|------|-----------|---------|
|ID|int32|||
|SoundExertionID|int32|[SoundEntries#ID](SoundEntries)||
|SoundExertionCriticalID|int32|[SoundEntries#ID](SoundEntries)||
|SoundInjuryID|int32|[SoundEntries#ID](SoundEntries)||
|SoundInjuryCriticalID|int32|[SoundEntries#ID](SoundEntries)||
|SoundInjuryCrushingBlowID|int32|||
|SoundDeathID|int32|[SoundEntries#ID](SoundEntries)||
|SoundStunID|int32|[SoundEntries#ID](SoundEntries)||
|SoundStandID|int32|[SoundEntries#ID](SoundEntries)||
|SoundFootstepID|int32|[FootstepTerrainLookup#CreatureFootstepID](FootstepTerrainLookup)||
|SoundAggroID|int32|[SoundEntries#ID](SoundEntries)||
|SoundWingFlapID|int32|[SoundEntries#ID](SoundEntries)||
|SoundWingGlideID|int32|[SoundEntries#ID](SoundEntries)||
|SoundAlertID|int32|[SoundEntries#ID](SoundEntries)||
|SoundFidget|int32[5]|[SoundEntries#ID](SoundEntries)||
|CustomAttack|int32[4]|[SoundEntries#ID](SoundEntries)||
|NPCSoundID|int32|||
|LoopSoundID|int32|[SoundEntries#ID](SoundEntries)||
|CreatureImpactType|int32|||
|SoundJumpStartID|int32|[SoundEntries#ID](SoundEntries)||
|SoundJumpEndID|int32|[SoundEntries#ID](SoundEntries)||
|SoundPetAttackID|int32|[SoundEntries#ID](SoundEntries)||
|SoundPetOrderID|int32|[SoundEntries#ID](SoundEntries)||
|SoundPetDismissID|int32|[SoundEntries#ID](SoundEntries)||
|FidgetDelaySecondsMin|float|||
|FidgetDelaySecondsMax|float|||
|BirthSoundID|int32|[SoundEntries#ID](SoundEntries)||
|SpellCastDirectedSoundID|int32|[SoundEntries#ID](SoundEntries)||
|SubmergeSoundID|int32|[SoundEntries#ID](SoundEntries)||
|SubmergedSoundID|int32|[SoundEntries#ID](SoundEntries)||
|CreatureSoundDataIDPet|int32|[CreatureSoundData#ID](CreatureSoundData)||
