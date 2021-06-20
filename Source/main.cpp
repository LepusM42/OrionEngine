/******************************************************************************!
* \file main.cpp
* \author Lepus
* \brief Entry point of the application.
*******************************************************************************/
#include "Orion.hpp" //OEPI
#include "UnitTest.h"
int main(int, char**)
{
	if (RunUnitTests()) return 1;
	//Go through the engine's entire life cycle.
	Orion::Engine orionEngine;
	orionEngine.Init();
	orionEngine.Update();
	orionEngine.Shutdown();
	//Exit the application.
	return 0;
}