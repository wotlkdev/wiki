---
layout: default
title: AreaTable
nav_exclude: true
---
# AreaTable

| Column | Type | Reference | Comment |
|--------|------|-----------|---------|
|ID|int32|||
|ContinentID|int32|[Map#ID](Map)||
|ParentAreaID|int32|[AreaTable#ID](AreaTable)||
|AreaBit|int32|||
|Flags|int32|||
|SoundProviderPref|int32|[SoundProviderPreferences#ID](SoundProviderPreferences)||
|SoundProviderPrefUnderwater|int32|[SoundProviderPreferences#ID](SoundProviderPreferences)||
|AmbienceID|int32|[SoundAmbience#ID](SoundAmbience)||
|ZoneMusic|int32|[ZoneMusic#ID](ZoneMusic)||
|IntroSound|int32|[ZoneIntroMusicTable#ID](ZoneIntroMusicTable)||
|ExplorationLevel|int32|||
|AreaName_lang|locstring|||
|FactionGroupMask|int32|||
|LiquidTypeID|int32[4]|[LiquidType#ID](LiquidType)||
|MinElevation|float|||
|Ambient_multiplier|float|||
|LightID|int32|[Light#ID](Light)||
