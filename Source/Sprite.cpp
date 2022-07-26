/*!*****************************************************************************
* \file Sprite.cpp
* \author Lepus
* \brief This is a template for other component files.
*******************************************************************************/
#include "Sprite.hpp"
#include "Renderer.hpp"
#include "Transform.hpp"
#include "Betel.hpp"
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
		char buffer[64] = "";

		ImGui::Text("Sprite");
		ImGui::InputText("Texture", buffer, 64);
		if (m_texture)
		{
			memcpy(buffer, m_texture->GetName().c_str(), 64);
			m_texture->SetName(buffer);
		}
		else
		{
			ImGui::InputText("Texture", buffer, 64);
			if (buffer != "")
			{
				std::cout << "MAKE A TEXTURE\n";
				SetTexture(buffer);
			}
		}
		ImGui::SliderFloat("R", &GetColor()[0], 0, 1, 0, 0);
		ImGui::SliderFloat("G", &GetColor()[1], 0, 1, 0, 0);
		ImGui::SliderFloat("B", &GetColor()[2], 0, 1, 0, 0);
	}

	void Sprite::Save(std::ostream& sceneFile)
	{
		sceneFile << "Sprite\n";
		for (auto tri : GetMesh().GetTriangles())
		{
			sceneFile << "Tri\n";
			sceneFile << tri.m_v1[0] << " " << tri.m_v1[1] << " " << tri.m_v1[2] << "\n";
			sceneFile << tri.m_v2[0] << " " << tri.m_v2[1] << " " << tri.m_v2[2] << "\n";
			sceneFile << tri.m_v3[0] << " " << tri.m_v3[1] << " " << tri.m_v3[2] << "\n";
		}
		sceneFile << "Color\n";
		sceneFile << GetColor()[0] << " " << GetColor()[1] << " " << GetColor()[2] << "\n";
		if (Texture* t = GetTexture())
		{
			sceneFile << "Texture\n";
			sceneFile << t->GetName() << "\n";
		}
		sceneFile << "EndComp\n";
	}

	void Sprite::Load(std::istream& sceneFile)
	{
		std::string str;
		float* triBuf = Betel::Allocate<float>(9);
		while (str != "EndComp")
		{
			sceneFile >> str;
			if (str == "EndComp") break;
			if (str == "Tri")
			{
				sceneFile >> triBuf[0] >> triBuf[1] >> triBuf[2];
				sceneFile >> triBuf[3] >> triBuf[4] >> triBuf[5];
				sceneFile >> triBuf[6] >> triBuf[7] >> triBuf[8];

				GetMesh().AddTriangle(
					Vertex({ triBuf[0], triBuf[1], triBuf[2] }),
					Vertex({ triBuf[3], triBuf[4], triBuf[5] }),
					Vertex({ triBuf[6], triBuf[7], triBuf[8] })
				);
			}
			if (str == "Color")
			{
				sceneFile >> GetColor()[0] >> GetColor()[1] >> GetColor()[2];
			}
			if (str == "Texture")
			{
				std::string texName;
				sceneFile >> texName;
				SetTexture(texName);
			}
		}
		Betel::Deallocate(triBuf);
		GetMesh().Init();
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