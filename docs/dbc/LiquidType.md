---
layout: default
title: LiquidType
nav_exclude: true
---
# LiquidType

| Column | Type | Reference | Comment |
|--------|------|-----------|---------|
|ID|int32|||
|Name|string|||
|Flags|int32|||
|SoundBank|int32|||
|SoundID|int32|[SoundEntries#ID](SoundEntries)||
|SpellID|int32|[Spell#ID](Spell)||
|MaxDarkenDepth|float|||
|FogDarkenIntensity|float|||
|AmbDarkenIntensity|float|||
|DirDarkenIntensity|float|||
|LightID|int32|[Light#ID](Light)||
|ParticleScale|float|||
|ParticleMovement|int32|||
|ParticleTexSlots|int32|||
|MaterialID|int32|[LiquidMaterial#ID](LiquidMaterial)||
|Texture|string[6]|||
|Color|int32[2]|||
|Float|float[18]|||
|Int|int32[4]|||
