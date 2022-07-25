/*!*****************************************************************************
* \file Example.hpp
* \author Lepus
* \brief This is a template for other component files.
*******************************************************************************/
#pragma once
#include <iostream>
#include <vector>
#include <list>
#include "Component.hpp"
#include "Entity.hpp"
#include "Transform.hpp"
#include "Sprite.hpp"

//lua library include files
extern "C"
{
#include "../lua542/include/lua.h"
#include "../lua542/include/lauxlib.h"
#include "../lua542/include/lualib.h"
}

namespace Orion
{
	class ScriptComponent;
	class Script
	{
	public:
		Script(std::string filename, ScriptComponent* parent);
		//execute lua code
		void Start();
		void Update();
		int DoString(std::string string);
		int DoFile(std::string filename);
		int CallLua(std::string funcName);
		bool Validate(int result);
		void Stop();
		template <typename T>
		void CreateUserData(T* base, std::string var)
		{
			lua_pushlightuserdata(m_luaState, base);
			lua_setglobal(m_luaState, var.c_str());
		}
		std::string m_filename;
		std::string m_shortname;
	private:
		ScriptComponent* m_parent{ nullptr };
		lua_State* m_luaState;
	};

	/*!*************************************************************************
	* \class Example
	* \brief Abstract class from which Objects are constructed.
	***************************************************************************/
	class ScriptComponent : public Component
	{
	public:
		ScriptComponent();
		void Start() override;
		void Update(float dt) override;
		void Stop() override;
		void DisplayImGui() override;
		~ScriptComponent();
		//add a script file by name
		void AddScript(std::string filename);
		Transform* GetTransform();
		Sprite* GetSprite();
		std::vector<Script> GetScripts();
	private:
		std::vector<Script> m_scripts;
		Transform* m_transform{ nullptr };
		Sprite* m_sprite{ nullptr };
		char m_imguiBuffer[64]{ "" };
	};
}