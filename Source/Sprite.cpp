/*!*****************************************************************************
* \file Sprite.cpp
* \author Lepus
* \brief This is a template for other component files.
*******************************************************************************/
#include "Sprite.hpp"
namespace Orion
{
	/*!*************************************************************************
	* \fn
	* \brief Constructor. Called only once, making it good for one-time initial
	*  allocations.
	* \param
	* \return
	***************************************************************************/
	Sprite::Sprite() :
		Component::Component()
	{

	}

	/*!*************************************************************************
	* \fn
	* \brief Called at least once in the constructor to initialize some
	*  properties. Can be called later upon the reset of this component.
	* \param
	* \return
	***************************************************************************/
	void Sprite::Start()
	{
		std::cout << "New ";
	}

	/*!*************************************************************************
	* \fn
	* \brief Update this component once every frame.
	* \param
	* \return
	***************************************************************************/
	void Sprite::Update(float)
	{

	}

	/*!*************************************************************************
	* \fn
	* \brief Called at least once in the destructor for basic cleanup. Can be
	*  called later upon the reset of this component.
	* \param
	* \return
	***************************************************************************/
	void Sprite::Stop()
	{

	}

	/*!*************************************************************************
	* \fn
	* \brief Constructor. Called only once, making it good for one-time initial
	*  allocations.
	* \param
	* \return
	***************************************************************************/
	Sprite::~Sprite()
	{

	}
}