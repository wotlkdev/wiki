#include "ScriptMgr.h"
#include "log.h"
// .. more includes
#include <string>
#include <chrono>
#include "Timescale.h"
#include <atomic>

//The namespace is what we use to contain our functions and variables.
//It allows us to call them like so: Timescale::StartTimescale();
namespace Timescale
{

	//A struct is a group of variables. We have to give it a unique type name after the "struct" statement.
	//We define it here, then create a variable to actually contain the data
    struct TimescaleYear {
        uint8 Second; //Resets every minute
        uint8 Minute; //Resets every hour
        uint8 Hour; //Resets every day
        uint8 Day; //Resets every month
        uint8 Week; //Resets every month
        uint8 Month; //Resets every year
        uint8 Season; //Resets every year
        uint16 Year; //Doesn't reset
    };
	
	//Now create the variable that contains it.
	//For variables, they're declared like so:
	//TheTypeOfVariable MyVariableName
	TimescaleYear TimescaleData;

	//Credit to @ktotes for this function!
	//This allows us to turn our timer's seconds count, into something known as PackedTime
	//WoW used PackedTime to store the game's current date and time
    uint32_t ToPackedTime(uint64_t epoch)
    {
        time_t seconds = (time_t)epoch;
        tm time;

        localtime_s(&time, &seconds);

        return (time.tm_year - 100) << 24 | time.tm_mon << 20 | (time.tm_mday - 1) << 14 | time.tm_wday << 11 | time.tm_hour << 6 | time.tm_min;
    }

	//This is where we will check the database for saved time values. If there aren't any, create a fallback time
	//And if the MySQL database doesn't have a table to save time values to, create it
    static void LoadFromDB()
    {

        //todo

    }

	//This will process our custom game timer, run by a separate thread to avoid blocking anything
	//Which will allow this to run on a different core.
	//In other words, we're multithreading!
    static void ProcessTimescale()
    {
        //todo

    }

	//This will be called by the timescale_loader_script.cpp file we created earlier
    void StartTimescale()
    {
        //todo

    }

	//Also called from the timescale_loader_script.cpp file
    void StopTimescale()
    {

        //todo

    }
    
}
