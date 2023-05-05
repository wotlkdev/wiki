//Create our own unique define. Whatever that is. It's important though
#ifndef __TIMESCALE_H
#define __TIMESCALE_H

//Needed for our custom script?
#include "Define.h"

//Same namespace name as in the .cpp file
namespace Timescale
{

	//Here we define all the functions inside the Timescale.cpp file, that will be called by other .cpp files
	//In this case, these functions will be used by the timescale_loader_script.cpp file we created
    TC_GAME_API void StartTimescale();

    TC_GAME_API void StopTimescale();

    TC_GAME_API float GetTimeSpeed();

    TC_GAME_API void ResetTickCounter();
}

#endif
