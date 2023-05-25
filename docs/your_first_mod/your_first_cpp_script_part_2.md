---
layout: default
title: Your First C++ Script (Part 2) (UNFINISHED) - Script Framework
nav_order: 6
---


# Your First C++ Script (Part 2) (UNFINISHED) - Script Framework

What we have done so far:

* Created the World script file
* Created the Timescale code (.cpp) file
* Created the Timescale header (.h) file
* Regenerated the Visual Studio project through CMake
* Cleaned the project in Visual Studio

Now we need to add the basic script boilerplate code to our timescale script, edit the world script list file, and prepare the actual Timescale code for being worked on.

## Editing `scripts_world\World\timescale_script_loader.cpp`

In Visual Studio, open the `timescale_script_loader.cpp` file we created before. Copy-paste the following code into it, and then read the comments I have written. Comments are the lines beginning with `//`:

```c++
#include "ScriptMgr.h"
#include "Define.h"
#include "SharedDefines.h"
// .. more includes

//This must be unique. A class contains our functions and data
//And it is spawned by the world_script_loader.cpp file
class fyty_timescale_script_loader_class : public WorldScript
{

public:

	//The type of script must be the same as the unique class name we declared above.
	//When the script file is created at runtime, it will have the name that we set inside the quotation marks.
	//Make sure it is also unique.
    fyty_timescale_script_loader_class() : WorldScript("fyty_timescale_loader_script") {}

	//This is called every tick by the World thread.
	//Never put anything intensive here. If you need something to be constantly processed, use another thread. Which is what we will do.
	//As the WorldUpdate thread runs on a single core, and the tick (by default) should take around a millisecond.
    void OnUpdate(uint32 diff) override
    {

        //todo: Tell the game to send our time data to all the players

    }

	//This is called when the server is starting up.
	//We will use this event to call our Timescale.cpp code, which will load any saved Timescale data
	//Or create it, if it doesn't exist
    void OnStartup() override
    {

        //todo: Load the saved time data, or create it if none exists

    }

	//This is called when the server is shutting down, and is terminating the game logic.
	//We will use this event to call our Timescape.cpp code, which saves the current Timescale data.
    void OnShutdown() override
    {
        
        //todo: Save the current time data, which will then be loaded the next time the server starts

    }

};

//This is the function that we will add to scripts_world\World\world_script_loader.cpp
//So our code will actually be processed
void AddSC_fyty_timescale_loader_script()
{

	//Use the same name as the class we declared at the beginning of our code
    new fyty_timescale_script_loader_class();

}
```

## Editing `scripts_world\World\world_script_loader.cpp`

By default, the file will have code that looks like the following:

```c++
#include "World.h"

// This is where scripts' loading functions should be declared:
// world
void AddSC_areatrigger_scripts();
void AddSC_emerald_dragons();
void AddSC_go_scripts();
void AddSC_npc_guard();
void AddSC_item_scripts();
void AddSC_npc_professions();
void AddSC_npc_innkeeper();
void AddSC_npcs_special();
void AddSC_achievement_scripts();
void AddSC_action_ip_logger();
void AddSC_duel_reset();
void AddSC_xp_boost();
// player
void AddSC_chat_log();
void AddSC_action_ip_logger();
//Custom

// The name of this function should match:
// void Add${NameOfDirectory}Scripts()
void AddWorldScripts()
{
    AddSC_areatrigger_scripts();
    AddSC_emerald_dragons();
    AddSC_go_scripts();
    AddSC_npc_guard();
    AddSC_item_scripts();
    AddSC_npc_professions();
    AddSC_npc_innkeeper();
    AddSC_npcs_special();
    AddSC_achievement_scripts();
    AddSC_chat_log(); // location: scripts\World\chat_log.cpp

    // FIXME: This should be moved in a script validation hook.
    // To avoid duplicate code, we check once /*ONLY*/ if logging is permitted or not.
    if (sWorld->getBoolConfig(CONFIG_IP_BASED_ACTION_LOGGING))
        AddSC_action_ip_logger(); // location: scripts\World\action_ip_logger.cpp
    AddSC_duel_reset();
    if (sWorld->getIntConfig(CONFIG_XP_BOOST_DAYMASK) != 0)
        AddSC_xp_boost();
}
```

Don't worry about what any of it does, we only want to do two things.
* Define the same function as the script creator in our `timescale_loader_script.cpp`'s function `AddSC_fyty_timescale_loader_script()` at the beginning of the file, with the return type `void`
    - `void` means the following function does not return a value after it has finished running.
* Add just the function call inside the `AddWorldScripts()` block
    - To keep things organized, I like to denote my edits with comments.
* With the above default code, it will now look like the following:

```c++
#include "World.h"

// This is where scripts' loading functions should be declared:
// world
void AddSC_areatrigger_scripts();
void AddSC_emerald_dragons();
void AddSC_go_scripts();
void AddSC_npc_guard();
void AddSC_item_scripts();
void AddSC_npc_professions();
void AddSC_npc_innkeeper();
void AddSC_npcs_special();
void AddSC_achievement_scripts();
void AddSC_action_ip_logger();
void AddSC_duel_reset();
void AddSC_xp_boost();
// player
void AddSC_chat_log();
void AddSC_action_ip_logger();
//Custom
//FyTy
void AddSC_fyty_timescale_loader_script();

// The name of this function should match:
// void Add${NameOfDirectory}Scripts()
void AddWorldScripts()
{
    AddSC_areatrigger_scripts();
    AddSC_emerald_dragons();
    AddSC_go_scripts();
    AddSC_npc_guard();
    AddSC_item_scripts();
    AddSC_npc_professions();
    AddSC_npc_innkeeper();
    AddSC_npcs_special();
    AddSC_achievement_scripts();
    AddSC_chat_log(); // location: scripts\World\chat_log.cpp

    AddSC_fyty_timescale_loader_script();

    // FIXME: This should be moved in a script validation hook.
    // To avoid duplicate code, we check once /*ONLY*/ if logging is permitted or not.
    if (sWorld->getBoolConfig(CONFIG_IP_BASED_ACTION_LOGGING))
        AddSC_action_ip_logger(); // location: scripts\World\action_ip_logger.cpp
    AddSC_duel_reset();
    if (sWorld->getIntConfig(CONFIG_XP_BOOST_DAYMASK) != 0)
        AddSC_xp_boost();
}
```