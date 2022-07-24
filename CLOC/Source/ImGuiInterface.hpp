/*!*****************************************************************************
* \file Stub.hpp
* \author Lepus
* \brief This is a stub file, used as a template for all other files.
*******************************************************************************/
#pragma once
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
namespace Orion
{
	namespace Cetus
	{
		static ImGuiContext* context;
		void Init(GLFWwindow* window);
		void Render();
		void Shutdown();
	}
}