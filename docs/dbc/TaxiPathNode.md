---
layout: default
title: TaxiPathNode
nav_exclude: true
---
# TaxiPathNode

| Column | Type | Reference | Comment |
|--------|------|-----------|---------|
|ID|int32|||
|PathID|int32|[TaxiPath#ID](TaxiPath)||
|NodeIndex|int32|||
|ContinentID|int32|[Map#ID](Map)||
|Loc|float[3]|||
|Flags|int32|||
|Delay|int32|||
|ArrivalEventID|int32|||
|DepartureEventID|int32|||
