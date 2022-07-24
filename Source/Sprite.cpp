/*!*****************************************************************************
* \file Sprite.cpp
* \author Lepus
* \brief This is a template for other component files.
*******************************************************************************/
#include "Sprite.hpp"
#include "Renderer.hpp"
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
	Sprite::Sprite() :
		Component::Component(),
		m_color(1.0f, 4)
	{
		std::cout << "sprite." << std::endl;
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
	* \brief Retrieve a reference to this sprite's mesh.
	* \param
	* \return
	***************************************************************************/
	Mesh& Sprite::GetMesh()
	{
		return m_mesh;
	}

	/*!*************************************************************************
	* \fn
	* \brief Retrieve a reference to this sprite's mesh.
	* \param
	* \return
	***************************************************************************/
	Texture* Sprite::GetTexture()
	{
		return m_texture;
	}

	/*!*************************************************************************
	* \fn
	* \brief Retrieve a reference to this sprite's mesh.
	* \param
	* \return
	***************************************************************************/
	void Sprite::SetTexture(std::string filename)
	{
		if (m_texture) delete m_texture;
		m_texture = new Texture(filename);
		m_texture->SetName(filename);
	}

	/*!*************************************************************************
	* \fn
	* \brief Retrieve a reference to this sprite's mesh.
	* \param
	* \return
	***************************************************************************/
	Rigel::Vector<float>& Sprite::GetColor()
	{
		return m_color;
	}

	/*!*************************************************************************
	* \fn
	* \brief Display data in IMGui.
	* \param
	* \return
	***************************************************************************/
	void Sprite::DisplayImGui()
	{
		ImGui::Text("Sprite");
		if (m_texture)
		{
			char buffer[64];
			memcpy(buffer, m_texture->GetName().c_str(), 64);
			ImGui::InputText("Texture", buffer, 64);
			SetTexture(buffer);
		}
		ImGui::SliderFloat("R", &GetColor()[0], 0, 1, 0, 0);
		ImGui::SliderFloat("G", &GetColor()[1], 0, 1, 0, 0);
		ImGui::SliderFloat("B", &GetColor()[2], 0, 1, 0, 0);
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