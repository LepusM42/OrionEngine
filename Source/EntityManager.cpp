/*!*****************************************************************************
* \file Example.cpp
* \author Lepus
* \brief This is a template for other component files.
*******************************************************************************/
#include "EntityManager.hpp"
#include "Betel.hpp"
#include "Sprite.hpp"
namespace Orion
{
	std::list<Entity*> EntityManager::m_entityPool;

	/*!*************************************************************************
	* \fn 
	* \brief Constructor. Called only once, making it good for one-time initial
	*  allocations.
	* \param 
	* \return 
	***************************************************************************/
	EntityManager::EntityManager()
	{

	}

	/*!*************************************************************************
	* \fn
	* \brief Update this component once every frame.
	* \param
	* \return
	***************************************************************************/
	void EntityManager::Update(float dt)
	{
		auto iter = m_entityPool.begin();
		for (Entity*& e : m_entityPool)
		{
			e->Update(dt);
			if (auto spr = e->Get<Sprite>())
			{
				spr->Update(0.0f);
			}
			if (e->MarkedForDestruction())
			{
				m_entityPool.erase(iter);
				Betel::Deallocate(e);
				e = nullptr;
			}
			iter++;
		}
	}

	/*!*************************************************************************
	* \fn
	* \brief Called at least once in the constructor to initialize some
	*  properties. Can be called later upon the reset of this component.
	* \param
	* \return
	***************************************************************************/
	void EntityManager::Add(Entity* e)
	{
		std::cout << "New ";
		m_entityPool.push_front(e);
	}

	/*!*************************************************************************
	* \fn
	* \brief Called at least once in the destructor for basic cleanup. Can be
	*  called later upon the reset of this component.
	* \param
	* \return
	***************************************************************************/
	void EntityManager::Remove(Entity* e)
	{

	}

	/*!*************************************************************************
	* \fn
	* \brief Constructor. Called only once, making it good for one-time initial
	*  allocations.
	* \param
	* \return
	***************************************************************************/
	EntityManager::~EntityManager()
	{
		if (m_entityPool.empty())
			return;
		for (auto iter = m_entityPool.begin(); iter != m_entityPool.end(); ++iter)
		{
			(*iter)->ClearComponents();
			Betel::Deallocate(*iter);
		}
		m_entityPool.clear();
	}
}