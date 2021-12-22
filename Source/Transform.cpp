/*!*****************************************************************************
* \file Transform.cpp
* \author Lepus
* \brief This is a template for other component files.
*******************************************************************************/
#include "Transform.hpp"
namespace Orion
{
	/*!*************************************************************************
	* \fn
	* \brief Constructor. Called only once, making it good for one-time initial
	*  allocations.
	* \param
	* \return
	***************************************************************************/
	Transform::Transform() :
		Component::Component()
	{
		std::cout << "transform." << std::endl;
	}

	/*!*************************************************************************
	* \fn
	* \brief Called at least once in the constructor to initialize some
	*  properties. Can be called later upon the reset of this component.
	* \param
	* \return
	***************************************************************************/
	void Transform::Start()
	{
		std::cout << "New ";
	}

	/*!*************************************************************************
	* \fn
	* \brief Update this component once every frame.
	* \param
	* \return
	***************************************************************************/
	void Transform::Update(float dt)
	{
		m_scale[0] = 1.000f;
		m_scale[1] = 1.000f;
	}

	/*!*************************************************************************
	* \fn
	* \brief Called at least once in the destructor for basic cleanup. Can be
	*  called later upon the reset of this component.
	* \param
	* \return
	***************************************************************************/
	void Transform::Stop()
	{

	}

	/*!*************************************************************************
	* \fn
	* \brief Constructor. Called only once, making it good for one-time initial
	*  allocations.
	* \param
	* \return
	***************************************************************************/
	Transform::~Transform()
	{

	}

	Rigel::Vector<float>& Transform::GetTranslation()
	{
		return m_translation;
	}

	Rigel::Vector<float>& Transform::GetScale()
	{
		return m_scale;
	}

	float& Transform::GetRotation()
	{
		return m_rotation;
	}
}