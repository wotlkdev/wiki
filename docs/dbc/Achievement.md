---
layout: default
title: Achievement
nav_exclude: true
---
# Achievement

| Column | Type | Reference | Comment |
|--------|------|-----------|---------|
|ID|int32|||
|Faction|int32|[Faction#ID](Faction)||
|Instance_ID|int32|[Map#ID](Map)||
|Supercedes|int32|[Achievement#ID](Achievement)||
|Title_lang|locstring|||
|Description_lang|locstring|||
|Category|int32|[Achievement_Category#ID](Achievement_Category)||
|Points|int32|||
|Ui_order|int32|||
|Flags|int32|||
|IconID|int32|[SpellIcon#ID](SpellIcon)||
|Reward_lang|locstring|||
|Minimum_criteria|int32|||
|Shares_criteria|int32|[Achievement#ID](Achievement)||
