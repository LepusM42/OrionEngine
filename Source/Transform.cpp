/*!*****************************************************************************
* \file Transform.cpp
* \author Lepus
* \brief This is a template for other component files.
*******************************************************************************/
#include "Transform.hpp"
#include <imgui.h>
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
		//scale
		s[0][0] = m_scale[0];
		s[1][1] = m_scale[1];
		s[2][2] = m_scale[2];
		s[3][3] = 1.0f;

		//rotation
		r[0][0] = cos(m_rotation);
		r[0][1] = -sin(m_rotation);
		r[1][0] = sin(m_rotation);
		r[1][1] = cos(m_rotation);
		
		//translation
		t[0][3] = m_translation[0];
		t[1][3] = m_translation[1];
		t[2][3] = m_translation[2];

		//putting it all together
		m_matrix = (s * r);

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
	* \brief Display data in IMGui.
	* \param
	* \return
	***************************************************************************/
	void Transform::DisplayImGui()
	{
		ImGui::Text("Transform");
		ImGui::InputFloat("Position X", &GetTranslation()[0]);
		ImGui::InputFloat("Position Y", &GetTranslation()[1]);
		ImGui::InputFloat("Position Z", &GetTranslation()[2]);
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

	Rigel::Matrix<float>& Transform::GetMatrix()
	{
		return m_matrix;
	}
}