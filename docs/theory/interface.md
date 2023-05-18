---
layout: default
title: Interface Files
nav_order: 3
---

# Interface Files

Interface files are commonly found in the `locale` MPQs inside the `Interface` and `AddOn` directories (inside the MPQ files) and are commonly used by modders to create custom interfaces for the game, similar to how player AddOns work.

There are three general categories of Interface Files:

1. **GlueXML**: Interface files displayed in the main menu, character selection and character creation menus.

2. **FrameXML**: Interface files displayed in the game after entering the world (Action Buttons, Quest Frames, Talent frame and so on).

3. **AddOns**: Contains internal Blizzard AddOns to the FrameXML UI, not to be confused with the `Interface/AddOns` directory in the game folders used for player AddOns.

## Loading Interface Files

**GlueXML** files are loaded by the game on startup, while **FrameXML** and **AddOns** are loaded when the player logs into the game or when they run the `/reload` chat command.

The game loads these files by using `.toc` files, which is a simple file containing Lua and XML filenames that the game should load. Adding custom interface files to the game is as simple as adding them to one of the Interface directories and writing that filename into the corresponding categories `.toc` file.

`.toc` files themselves are read on startup, and it is necessary to restart the client for changes to them to take effect.

## GlueXML

GlueXML files are placed in the `Interface/GlueXML` directory, and uses the .toc file `Interface/GlueXML/GlueXML.toc`. The most important GlueXML files are:

- `AccountLogin.lua` / `AccountLogin.xml`: Defines the login screen.
- `CharaterSelect.lua` / `CharacterSelect.xml`: Defines the character selection screen
- `CharacterCreate.lua` / `CharacterCreate.xml`: Defines the character creation screen
- `RealmList.lua` / `RealmList.xml`: Defines the realm list box
- `GlueStrings.lua` / `GlueStrings.xml`: Defines the various text fields found in the other "Glue" interfaces.

<img src="https://i.imgur.com/HdVRxOI.png">

## FrameXML

FrameXML files are placed in the `Interface/FrameXML` directory, and uses the .toc file `Interface/FrameXML/FrameXML.toc`.

There are too many FrameXML interface files to go over all of them, but it is generally not too difficult to find what you're looking for aside from a few cases where FrameXML is actually loaded from the `AddOn` directory instead, so it's important to keep an eye on both.

<img src="https://i.imgur.com/Q3VdMfS.png">

## AddOns

Internal AddOns are placed in the `Interface/AddOns` directory. Inside this directory there are additional directories that all contain their own `.toc` files, which works the same way as player AddOns.

<img src="https://i.imgur.com/OTNnFt8.png">

## Native Functions

Many parts of the internal Blizzard interfaces are not actually defined in Lua or XML files, but are internal functions in the client exe itself.

This means that not all parts of the client interface are easily replaceable, because for some of them large parts of their implementations is machine code, and sometimes requires techniques like `function overwriting` or, for very bad cases, rewriting entire interfaces to support editing.

## Function Overwriting

When files in the `.toc` files are loaded by the game, all variables and functions not marked as `local` end up in a global namespace that all files defined after them can access, but also override.

For example, if a file `lua_a.lua` contains the following code:

```lua
-- lua_a.lua
function my_function_a()
    print("Hello World")
end

function main_function()
    my_function_a()
end
```

Another file loaded after it, `lua_b.lua`, can **overwrite** the implementation of `my_function_a()` by simple defining the function again:

```lua
-- lua_b.lua

-- Storing the old function like this is a common method to allow calling it if we should need to
local old_my_function_a = my_function_a
function my_function_a()
    print("Overwrote the old function, now calling it:")
    old_my_function_a()
end
```

This change will also apply to previously loaded files, so if were to call the `main_function` defined in `lua_a.lua`, it would still call our overwritten function in `lua_b.lua`.

This method also works for _native functions_ defined in the client exe itself, which can sometimes allow us to modify parts of the client interface that are not normally accessible.