---
layout: default
title: FactionTemplate
nav_exclude: true
---
# FactionTemplate

| Column | Type | Reference | Comment |
|--------|------|-----------|---------|
|ID|int32|||
|Faction|int32|[Faction#ID](Faction)||
|Flags|int32|||
|FactionGroup|int32|[FactionGroup#ID](FactionGroup)||
|FriendGroup|int32|||
|EnemyGroup|int32|||
|Enemies|int32[4]|[Faction#ID](Faction)||
|Friend|int32[4]|[Faction#ID](Faction)||
