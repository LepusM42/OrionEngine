/*!*****************************************************************************
* \file Stub.cpp
* \author Lepus
* \brief This is a stub file, used as a template for all other files.
*******************************************************************************/
#include "ImGuiInterface.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"
#include "Sprite.hpp"
#include "ScriptComponent.hpp"
#include "Transform.hpp"
#include "Betel.hpp"
#include <string>
#include <iostream>
namespace Orion
{
	namespace Cetus
	{
		std::vector<char*> buffer;
		void Init(GLFWwindow* window)
		{
			IMGUI_CHECKVERSION();
			context = ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO();
			ImGui_ImplGlfw_InitForOpenGL(window, true);
			ImGui_ImplOpenGL3_Init("#version 330");
			ImGui::StyleColorsDark();

			auto pool = EntityManager::Pool();
			for (auto entity : pool)
			{
				buffer.push_back(new char[64]());
			}
		}
		Entity* currentEntity{ nullptr };
		int itemCurrent = 0;
		void MakeGUI(std::string title)
		{
			ImGui::Begin(title.c_str());

			if (ImGui::Button("New Game Object"))
			{
				CreateEntity();
				buffer.push_back(new char[64]());
			}

			if (currentEntity && buffer.size() > itemCurrent)
			{
				ImGui::InputText("Object Name", buffer[itemCurrent], 64);
				currentEntity->m_name = buffer[itemCurrent];
				currentEntity->DisplayComponents();
				if (ImGui::BeginMenu("AddComponent"))
				{
					bool transformSelected, spriteSelected, scriptSelected;
					if (ImGui::MenuItem("Transform", "1", &transformSelected))
					{
						currentEntity->AddNew<Transform>();
					}
					if (ImGui::MenuItem("Sprite", "2", &spriteSelected))
					{
						currentEntity->AddNew<Sprite>();
					}
					if (ImGui::MenuItem("Script", "3", &scriptSelected))
					{
						currentEntity->AddNew<ScriptComponent>();
					}
					ImGui::EndMenu();
				}
			}

			ImGui::End();

			ImGui::Begin("Objects in Scene");
			auto pool = EntityManager::Pool();
			std::vector<const char*> namePool;
			for (auto entity : pool)
			{
				namePool.push_back(entity->m_name.c_str());
			}
			ImGui::ListBox("Objects", &itemCurrent, namePool.data(), namePool.size());
			currentEntity = pool[itemCurrent];
			ImGui::End();
		}
		void Render()
		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			MakeGUI("Cetus Editor");
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			ImGui::EndFrame();
		}
		void Shutdown()
		{
			ImGui_ImplGlfw_Shutdown();
			ImGui_ImplOpenGL3_Shutdown();
			ImGui::DestroyContext(context);
			for (auto b : buffer)
			{
				delete[] b;
			}
		}
	}
}