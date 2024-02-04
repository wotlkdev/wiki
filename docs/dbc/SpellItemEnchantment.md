---
layout: default
title: SpellItemEnchantment
nav_exclude: true
---
# SpellItemEnchantment

| Column | Type | Reference | Comment |
|--------|------|-----------|---------|
|ID|int32|||
|Charges|int32|||
|Effect|int32[3]|||
|EffectPointsMin|int32[3]|||
|EffectPointsMax|int32[3]|||
|EffectArg|int32[3]|[Spell#ID](Spell)||
|Name_lang|locstring|||
|ItemVisual|int32|[ItemVisuals#ID](ItemVisuals)||
|Flags|int32|||
|Src_itemID|int32|||
|Condition_ID|int32|[SpellItemEnchantmentCondition#ID](SpellItemEnchantmentCondition)||
|RequiredSkillID|int32|[SkillLine#ID](SkillLine)||
|RequiredSkillRank|int32|||
|MinLevel|int32|||
