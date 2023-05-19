---
layout: default
title: Core Scripts
nav_order: 9
---

# Core Scripts

Scripts are used to implement special behavior for specific spells, creatures, instances or commands, where the core cannot rely on generic behaviors that generalize to large groups of entities, such as spells or small groups of spells that have highly special behaviors that no other spells have.

All scripts in the core can be found in the [scripts](https://github.com/TrinityCore/TrinityCore/tree/3.3.5/src/server/scripts) directory in the core repository. Here, scripts are divided into some generic categories that all have roughly the same format.

## Script Loading

Each script category contains a special _loader_ file, that usually has the format `<x>_script_loader.cpp`. For example:
- [battlefield_script_loader.cpp](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/scripts/Battlefield/battlefield_script_loader.cpp)
- [cs_script_loader.cpp](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/scripts/Commands/cs_script_loader.cpp)
- [**custom_script_loader.cpp**](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/scripts/Custom/custom_script_loader.cpp)
- [eastern_kingdoms_script_loader.cpp](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/scripts/EasternKingdoms/eastern_kingdoms_script_loader.cpp)
- [spell_script_loader.cpp](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/scripts/Spells/spell_script_loader.cpp)

These files all contain a single implemented function called `AddXScripts`, whose only purpose is to initialize all the other script files in the current folder. This function is itself called from an auto-generated file inside the core, depending on what scripts were defined to be compiled in the build settings.

When adding new script files with their own initialization functions, it is **necessary** to both add its function declaration to the corresponding `script_loader` file and also **call** that function inside the script loader function. Not doing this means the added script will not be loaded into the core.

## Script Structure

Most script consists of classes that contain **event handlers** and **virtual methods**, and are meant to be extended and implemented by specific script subclasses in the `scripts` folder.

Event handlers are registered in the scripts `Register` method, and can support multiple handlers in the same script, while **virtual methods** are meant to be implemented once by the script subclass. Basic examples of this will be provided below.

## Case study: Spell Scripts

Spell scripts are classes that inherit from the [SpellScript](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Spells/SpellScript.h#:~:text=class%20TC_GAME_API%20SpellScript) class.
- example virtual methods: 
    - [_SpellScript::Register](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Spells/SpellScript.h#:~:class%20TC_GAME_API%20virtual%20void%20Register): Used to register event handlers
    - [_SpellScript::Validate](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Spells/SpellScript.h#:~:text=virtual%20bool%20Validate): Used to ensure dbc/database related to the spell is correct

- example event handlers:
    - [_SpellScript::BeforeCast](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Spells/SpellScript.h#:~:text=Hooklist%3CCastHandler%3E%20BeforeCast)
    - [_SpellScript::OnCast](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Spells/SpellScript.h#:~:text=Hooklist%3CCastHandler%3E%20OnCast)
    - [_SpelScript::AfterCast](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/src/server/game/Spells/SpellScript.h#:~:text=Hooklist%3CCastHandler%3E%20AfterCast)

For example, here is an implementation for a basic spell script class

```c++
#include "SpellScript.h"
#include <iostream>

class my_spell_script: public SpellScript
{
    // normal method, does not register to anything on its own
    void on_cast()
    {
        std::cout << "Hello world from my_spell_script\n";
    }

    // virtual function override
    void Register() override
    {
        // register on_cast to be an event handler
        OnCast += SpellCastFn(my_spell_cript::on_cast);
    }
}

// registry function (must be called manually from the script categories script loader!)
void AddSC_my_spell_scripts()
{
    RegisterSpellScript(my_spell_script);
}
```

To tie a specific spell id to a SpellScript, we use the server world database table [spell_script_names](https://trinitycore.info/en/database/335/world/spell_script_names), where the `ScriptName` column in that table maps to the class name we register in the `RegisterSpellScript` function. This allows the core to easily tie the same spell script to multiple spells without recompiling.

## Other Script Types

Other script types sometimes work similar to Spell scripts, like Aura scripts, while others like Creature scripts are sometimes nest classes of event handlers for more control in how to register behavior. It's usually enough to look at a couple of examples to understand how to implement them for new entities.