/******************************************************************************!
* \file main.cpp
* \author Lepus
* \brief Entry point of the application.
*******************************************************************************/
#include "Orion.hpp" //OEPI
int main(int, char**)
{
	//Go through the engine's entire life cycle.
	Orion::Engine::Init();
	Orion::Engine::Update();
	Orion::Engine::Exit();
	//Exit the application.
	return 0;
}