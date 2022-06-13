/*!*****************************************************************************
* \file Example.cpp
* \author Lepus
* \brief This is a template for other component files.
*******************************************************************************/
#include "SceneManager.hpp"
#include "EntityManager.hpp"
#include "Betel.hpp"
#include "Sprite.hpp"
#include "Transform.hpp"
#include "ScriptComponent.hpp"
#include <fstream>
namespace Orion
{
	/*!*************************************************************************
	* \fn 
	* \brief Constructor. Called only once, making it good for one-time initial
	*  allocations.
	* \param 
	* \return 
	***************************************************************************/
	SceneManager::SceneManager()
	{

	}

	/*!*************************************************************************
	* \fn
	* \brief Called at least once in the constructor to initialize some
	*  properties. Can be called later upon the reset of this component.
	* \param
	* \return
	***************************************************************************/
	void SceneManager::Load(std::string name)
	{
		std::ifstream sceneFile(name);
		std::string str;
		Entity* e = nullptr;
		while (!sceneFile.eof())
		{
			sceneFile >> str;
			if (str == "StartObj")
			{
				std::cout << "New Object\n";
				e = Betel::Allocate<Entity>();
			}
			if (str == "EndObj")
			{
				EntityManager::Add(e);
				e = nullptr;
			}
			if (str == "Name:")
			{
				if (!e) continue;
				sceneFile >> str;
				e->m_name = str;
				std::cout << "Name: " << e->m_name << "\n";
			}
			if (str == "Sprite")
			{
				Sprite* spr = Betel::Allocate<Sprite>();
				if (!e || !spr) continue;
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

						spr->GetMesh().AddTriangle(
							Vertex({ triBuf[0], triBuf[1], triBuf[2] }),
							Vertex({ triBuf[3], triBuf[4], triBuf[5] }),
							Vertex({ triBuf[6], triBuf[7], triBuf[8] })
						);
					}
					if (str == "Color")
					{
						sceneFile >> spr->GetColor()[0] >> spr->GetColor()[1] >> spr->GetColor()[2];
					}
				}
				Betel::Deallocate(triBuf);
				spr->GetMesh().Init();
				e->Add(spr);
				spr->Start();
			}
			if (str == "Transform")
			{
				Transform* spr = Betel::Allocate<Transform>();
				if (!e || !spr) continue;
				while (str != "EndComp")
				{
					sceneFile >> str;
					if (str == "EndComp") break;
					if (str == "Translation")
					{
						sceneFile >> spr->GetTranslation()[0];
						sceneFile >> spr->GetTranslation()[1];
						sceneFile >> spr->GetTranslation()[2];
					}
					if (str == "Scale")
					{
						sceneFile >> spr->GetScale()[0];
						sceneFile >> spr->GetScale()[1];
						sceneFile >> spr->GetScale()[2];
					}
					if (str == "Rotation")
					{
						sceneFile >> spr->GetRotation();
					}
				}
				e->Add(spr);
				spr->Start();
			}
			if (str == "ScriptComponent")
			{
				ScriptComponent* spr = Betel::Allocate<ScriptComponent>();
				if (!e || !spr) continue;
				while (str != "EndComp")
				{
					sceneFile >> str;
					if (str == "EndComp") break;
					spr->AddScript(str);
				}
				e->Add(spr);
				spr->Start();
			}
		}
	}

	/*!*************************************************************************
	* \fn
	* \brief Called at least once in the destructor for basic cleanup. Can be
	*  called later upon the reset of this component.
	* \param
	* \return
	***************************************************************************/
	void SceneManager::Save(std::string name)
	{

	}

	/*!*************************************************************************
	* \fn
	* \brief Constructor. Called only once, making it good for one-time initial
	*  allocations.
	* \param
	* \return
	***************************************************************************/
	SceneManager::~SceneManager()
	{

	}
}