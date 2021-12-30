/*!*****************************************************************************
* \file Example.hpp
* \author Lepus
* \brief This is a template for other component files.
*******************************************************************************/
#pragma once
#include <iostream>
#include <vector>
#include "Component.hpp"
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
		int DoString(std::string string);
		int DoFile(std::string filename);
		int RegisterFunction(std::string funcName, int(*func)(lua_State*));
		int CallLua(std::string funcName, int argc, int retc);
		int CallC(std::string funcName, int(*func)(lua_State*), int argc, int retc);
		void Validate(int result);
		void Stop();
	private:
		ScriptComponent* m_parent{ nullptr };
		std::string m_filename;
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
		~ScriptComponent();
		//add a script file by name
		void AddScript(std::string filename);
	private:
		std::vector<Script> m_scripts;
		Transform* m_transform{ nullptr };
		Sprite* m_sprite{ nullptr };
	};
}