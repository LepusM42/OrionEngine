/*!*****************************************************************************
* \file Entity.cpp
* \author Lepus
* \brief This is a stub file, used as a template for all other files.
*******************************************************************************/
#include "Entity.hpp"
#include "Component.hpp"
#include "Betel.hpp"
namespace Orion
{
	/*!*************************************************************************
	* \fn 
	* \brief 
	* \param 
	* \return 
	***************************************************************************/
	void Entity::Add(Component* component)
	{
		component->SetParent(this);
		m_components.push_back(component);
	}

	/*!*************************************************************************
	* \fn
	* \brief
	* \param
	* \return
	***************************************************************************/
	void Entity::Start()
	{
		for (Component* component : m_components)
		{
			component->Start();
		}
	}

	/*!*************************************************************************
	* \fn
	* \brief
	* \param
	* \return
	***************************************************************************/
	void Entity::Update(float dt)
	{
		for (Component* component : m_components)
		{
			component->Update(dt);
		}
	}

	/*!*************************************************************************
	* \fn
	* \brief
	* \param
	* \return
	***************************************************************************/
	void Entity::Stop()
	{
		for (Component* component : m_components)
		{
			component->Stop();
		}
	}
}