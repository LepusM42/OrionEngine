/*!*****************************************************************************
* \file Entity.cpp
* \author Lepus
* \brief This is a stub file, used as a template for all other files.
*******************************************************************************/
#include "Entity.hpp"
#include "EntityManager.hpp"
#include "Component.hpp"
#include "Betel.hpp"
#include "Transform.hpp"
#include "Sprite.hpp"
#include <imgui.h>
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

	//! Mark for destruction
	void Entity::Destroy()
	{
		m_marked = true;
	}

	//! Marked for destruction?
	bool Entity::MarkedForDestruction()
	{
		return m_marked;
	}

	//! Remove all components
	void Entity::ClearComponents()
	{
		for (Component* component : m_components)
		{
			component->Stop();
			Betel::Deallocate(component);
		}
		m_components.clear();
	}

	//! Display all components in ImGui
	void Entity::DisplayComponents()
	{
		for (auto component = m_components.begin(); component != m_components.end(); ++component)
		{
			(*component)->DisplayImGui();
			if (ImGui::Button("Remove Component"))
			{
				m_components.erase(component);
				return;
			}
		}
	}

	//! Serialization
	void Entity::Save(std::ostream& sceneFile)
	{
		for (Component* component : m_components)
		{
			component->Save(sceneFile);
		}
	}

	//! Make a new blank entity
	Entity* CreateEntity()
	{
		Entity* e = Betel::Allocate<Entity>();

		Transform* t = Betel::Allocate<Transform>();
		Sprite* s = Betel::Allocate<Sprite>();

		float p1[3] = { -.5,-.5,0 };
		float p2[3] = { .5,.5,0 };
		float p3[3] = { -.5,.5,0 };
		float p4[3] = { .5,-.5,0 };

		Vertex v1 = Vertex(p1, 3);
		Vertex v2 = Vertex(p2, 3);
		Vertex v3 = Vertex(p3, 3);
		Vertex v4 = Vertex(p4, 3);

		s->GetMesh().AddTriangle(v2, v4, v1);
		s->GetMesh().AddTriangle(v2, v1, v3);
		s->GetMesh().Init();
		s->GetColor()[0] = 1;
		s->GetColor()[1] = .5;
		s->GetColor()[2] = .5;
		s->GetColor()[3] = 1;
		e->Add(s);
		s->Start();

		t->GetTranslation() = Rigel::Vector<float>(0.0f, 3);
		t->GetScale() = Rigel::Vector<float>(200.0f, 3);
		e->Add(t);
		t->Start();

		EntityManager::Add(e);

		return e;
	}
}