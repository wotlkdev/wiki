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
