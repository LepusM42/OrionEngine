/*!*****************************************************************************
* \file Stub.cpp
* \author Lepus
* \brief This is a stub file, used as a template for all other files.
*******************************************************************************/
#include "ImGuiInterface.hpp"
#include "Entity.hpp"
#include <string>
#include <iostream>
namespace Orion
{
	namespace Cetus
	{
		void Init(GLFWwindow* window)
		{
			IMGUI_CHECKVERSION();
			context = ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO();
			ImGui_ImplGlfw_InitForOpenGL(window, true);
			ImGui_ImplOpenGL3_Init("#version 330");
			ImGui::StyleColorsDark();
		}
		void MakeGUI(std::string title)
		{
			ImGui::SetNextWindowSize(ImVec2(200, 100));
			ImGui::Begin(title.c_str());

			if (ImGui::Button("New Game Object")) CreateEntity();

			if (ImGui::BeginMenu("Menu"))
			{
				ImGui::EndMenu();
			}

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
		}
	}
}