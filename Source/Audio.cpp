/*!*****************************************************************************
* \file Audio.cpp
* \author Lepus
* \brief This is a template for other component files.
*******************************************************************************/
#include "Audio.hpp"
namespace Orion
{
	/*!*************************************************************************
	* \fn 
	* \brief Constructor. Called only once, making it good for one-time initial
	*  allocations.
	* \param 
	* \return 
	***************************************************************************/
	Audio::Audio() :
		Component::Component()
	{

	}

	/*!*************************************************************************
	* \fn
	* \brief Update this component once every frame.
	* \param
	* \return
	***************************************************************************/
	void Audio::Update(float)
	{

	}

	/*!*************************************************************************
	* \fn
	* \brief Called at least once in the constructor to initialize some
	*  properties. Can be called later upon the reset of this component.
	* \param
	* \return
	***************************************************************************/
	void Audio::Start()
	{
		std::cout << "New ";
	}

	/*!*************************************************************************
	* \fn
	* \brief Called at least once in the destructor for basic cleanup. Can be
	*  called later upon the reset of this component.
	* \param
	* \return
	***************************************************************************/
	void Audio::Stop()
	{

	}

	/*!*************************************************************************
	* \fn
	* \brief Constructor. Called only once, making it good for one-time initial
	*  allocations.
	* \param
	* \return
	***************************************************************************/
	Audio::~Audio()
	{

	}
}