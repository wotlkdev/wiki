# FactionTemplate

| Column | Type | Reference | Comment |
|--------|------|-----------|---------|
|ID|int32|||
|Faction|int32|[Faction#ID](Faction.md)||
|Flags|int32|||
|FactionGroup|int32|[FactionGroup#ID](FactionGroup.md)||
|FriendGroup|int32|||
|EnemyGroup|int32|||
|Enemies|int32[4]|[Faction#ID](Faction.md)||
|Friend|int32[4]|[Faction#ID](Faction.md)||
