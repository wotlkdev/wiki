---
layout: default
title: Talent
nav_exclude: true
---
# Talent

| Column | Type | Reference | Comment |
|--------|------|-----------|---------|
|ID|int32|||
|TabID|int32|||
|TierID|int32|||
|ColumnIndex|int32|||
|SpellRank|int32[9]|||
|PrereqTalent|int32[3]|[Talent#ID](Talent)||
|PrereqRank|int32[3]|||
|Flags|int32|||
|RequiredSpellID|int32|[Spell#ID](Spell)||
|CategoryMask|int32[2]|||
