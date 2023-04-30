# AreaTable

| Column | Type | Reference | Comment |
|--------|------|-----------|---------|
|ID|int32|||
|ContinentID|int32|[Map#ID](Map.md)||
|ParentAreaID|int32|[AreaTable#ID](AreaTable.md)||
|AreaBit|int32|||
|Flags|int32|||
|SoundProviderPref|int32|[SoundProviderPreferences#ID](SoundProviderPreferences.md)||
|SoundProviderPrefUnderwater|int32|[SoundProviderPreferences#ID](SoundProviderPreferences.md)||
|AmbienceID|int32|[SoundAmbience#ID](SoundAmbience.md)||
|ZoneMusic|int32|[ZoneMusic#ID](ZoneMusic.md)||
|IntroSound|int32|[ZoneIntroMusicTable#ID](ZoneIntroMusicTable.md)||
|ExplorationLevel|int32|||
|AreaName_lang|locstring|||
|FactionGroupMask|int32|||
|LiquidTypeID|int32[4]|[LiquidType#ID](LiquidType.md)||
|MinElevation|float|||
|Ambient_multiplier|float|||
|LightID|int32|[Light#ID](Light.md)||
