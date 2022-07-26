/*!*****************************************************************************
* \file Component.cpp
* \author Lepus
* \brief This is a stub file, used as a template for all other files.
*******************************************************************************/
#include "Component.hpp"
#include "Entity.hpp"
namespace Orion
{
	/*!*************************************************************************
	* \fn 
	* \brief Constructor. Called only once, making it good for one-time initial
	*  allocations.
	* \param 
	* \return 
	***************************************************************************/
	Component::Component()
	{
		std::cout << "New ";
	}

	/*!*************************************************************************
	* \fn
	* \brief Called at least once in the constructor to initialize some
	*  properties. Can be called later upon the reset of this component.
	* \param
	* \return
	***************************************************************************/
	void Component::Start()
	{

	}

	/*!*************************************************************************
	* \fn
	* \brief Update this component once every frame.
	* \param
	* \return
	***************************************************************************/
	void Component::Update(float)
	{

	}

	/*!*************************************************************************
	* \fn
	* \brief Called at least once in the destructor for basic cleanup. Can be
	*  called later upon the reset of this component.
	* \param
	* \return
	***************************************************************************/
	void Component::Stop()
	{

	}

	/*!*************************************************************************
	* \fn
	* \brief Reset the state of this component.
	* \param
	* \return
	***************************************************************************/
	void Component::Reset()
	{
		Stop();
		Start();
	}

	/*!*************************************************************************
	* \fn
	* \brief Get another Component from the Entity to which this belongs.
	* \param
	* \return
	***************************************************************************/
	template <typename ComponentType>
	ComponentType* Component::Get()
	{
		ComponentType* c = m_parent->Get<ComponentType>();
		return dynamic_cast<ComponentType*>(c);
	}

	/*!*************************************************************************
	* \fn
	* \brief Set the parent Entity of this component. Can only be done once.
	* \param
	* \return
	***************************************************************************/
	void Component::SetParent(Entity* parent)
	{
		if (m_parent == nullptr)
		{
			m_parent = parent;
		}
	}

	/*!*************************************************************************
	* \fn
	* \brief Display data in IMGui.
	* \param
	* \return
	***************************************************************************/
	void Component::DisplayImGui()
	{

	}

	/*!*************************************************************************
	* \fn
	* \brief Serialization.
	* \param
	* \return
	***************************************************************************/
	void Component::Save(std::ostream& os)
	{

	}

	/*!*************************************************************************
	* \fn
	* \brief Serialization.
	* \param
	* \return
	***************************************************************************/
	void Component::Load(std::istream& is)
	{

	}

	/*!*************************************************************************
	* \fn
	* \brief Destructor. Called only once, and cleans up any remaining allocated
	*  objects.
	* \param
	* \return
	***************************************************************************/
	Component::~Component()
	{

	}
}