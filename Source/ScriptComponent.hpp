/*!*****************************************************************************
* \file Example.hpp
* \author Lepus
* \brief This is a template for other component files.
*******************************************************************************/
#pragma once
#include <iostream>
#include <vector>
#include "Component.hpp"

//lua library include files
extern "C"
{
#include "../lua542/include/lua.h"
#include "../lua542/include/lauxlib.h"
#include "../lua542/include/lualib.h"
}

namespace Orion
{
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
		void AddScript(std::string filename);
	private:
		std::vector<std::string> m_scriptFiles;
		static lua_State* m_luaState;
	};
}