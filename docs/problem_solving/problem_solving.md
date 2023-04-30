---
layout: default
title: Problem Solving
nav_order: 4
---

## Problem Solving

This section will discuss how to actually handle problems in development, strategies to avoid them, and to identify and solve them effectively when they show up.

To make the sections more readable, I will use the following denotions:

- **Positive**: Means that we have a problem and are able to reproduce it.
- **Negative**: Means that we are unable to reproduce a problem.
- **Symptom**: Signs of a problem
- **Cause**: Root of a problem or subproblem
- **Regression**: Changes causing bugs or adverse effects to **previous** functionality.

### Losing a Positive

Once we have identified a _positive_ in our system, it may be tempting to try to get rid of by any means possible. However, a positive disappearing underneath our noses can sometimes be a bad thing, especially if we don't learn how it was introduced, and even worse if we don't learn how it disappeared.

### Dangers of 'Reasoning'

Being able to logically reason about modifications you've made to the game, how they should behave and what kind of problem a given set of symptoms often indicate is of course a very important skill to have as a modder. Many problems in the game are highly predictable, and something that you learn to pick up on the more you see them.

However, one very common mistake that beginners make is relying **too much** on reason alone to figure out what might be going wrong with their mods. This can often be ineffective for a few reasons:

- It often assumes that you have made your modification correctly on every step along the way
- It often assumes your tutorial is up-to-date and that you operate on correct information
- It often assumes that your problem stems from the problem you are _currently_ trying to solve, rather than something you did previously, or a combination of changes you are trying to make.
- It often assumes that the nature of symptoms are indicative of the nature of the problem.

### Version Control

Creating mods often involve editing large amount of different files, and even a single contained modification can contain a lot of complicated steps that can very easily go wrong along the way.

Version control are methods and tools used to create 'snapshots' of the state of our projects as we go to help us navigate and retrace the steps we've taken.

#### Tools

There are a few commonly used methods for version control, each with their own pros and cons.

##### 'Creating a copy of a file before editing it'

For quick edits and tests, it can sometimes be sufficient to just create a copy so you can easily revert any changes made to it if it inflicts a major regression. This can be good enough when working with a handful of `.dbc` files, but makes it hard to apply the more advanced version control strategies we will discuss below.

##### Git

Git is the most commonly used method for version control in WoW modding. It is a very powerful tool enabling most of the advanced 

- Version Control
    - Alternatives, Pros and Cons
    - Diff Views
    - Bisecting
    - Snapshotting
    - Squashing
    - Last working state
- Tracing and Debugging
    - When to trace
    - When to debug
- Divide and Conquer
    - Binary Search
    - Fuzzing
    - Corkscrew
    - Choosing violence
- Path of Balanced Resistance