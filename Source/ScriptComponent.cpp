/*!*****************************************************************************
* \file Example.cpp
* \author Lepus
* \brief This is a template for other component files.
*******************************************************************************/
#include "ScriptComponent.hpp"

namespace Orion
{
	//Static declarations
	lua_State* ScriptComponent::m_luaState = nullptr;

	/*!*************************************************************************
	* \fn 
	* \brief Constructor. Called only once, making it good for one-time initial
	*  allocations.
	* \param 
	* \return 
	***************************************************************************/
	ScriptComponent::ScriptComponent() :
	Component::Component()
	{
		std::cout << "script component." << std::endl;
	}

	/*!*************************************************************************
	* \fn
	* \brief Update this component once every frame.
	* \param
	* \return
	***************************************************************************/
	void ScriptComponent::Update(float)
	{

	}

	/*!*************************************************************************
	* \fn
	* \brief Called at least once in the constructor to initialize some
	*  properties. Can be called later upon the reset of this component.
	* \param
	* \return
	***************************************************************************/
	void ScriptComponent::Start()
	{
		//Initialize empty lua state
		if (!m_luaState)
		{
			m_luaState = luaL_newstate();
			luaL_openlibs(m_luaState);
		}
		//Begin execution of all scripts
		for (auto script : m_scriptFiles)
		{
			std::cout << "Running " << script << "\n";
			int result = luaL_dofile(m_luaState, script.c_str());
			if (result == LUA_OK)
			{
				std::cout << "LUA operation successful.\n";
			}
			else
			{
				std::cout << "LUA operation unsuccessful.\n";
				std::cout << lua_tostring(m_luaState, -1) << "\n";
				lua_pop(m_luaState, 1);
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
	void ScriptComponent::Stop()
	{
		lua_close(m_luaState);
	}

	/*!*************************************************************************
	* \fn
	* \brief Constructor. Called only once, making it good for one-time initial
	*  allocations.
	* \param
	* \return
	***************************************************************************/
	ScriptComponent::~ScriptComponent()
	{

	}

	/*!*************************************************************************
	* \fn
	* \brief Constructor. Called only once, making it good for one-time initial
	*  allocations.
	* \param
	* \return
	***************************************************************************/
	void ScriptComponent::AddScript(std::string filename)
	{
		filename = "Scripts/" + filename + ".lua";
		m_scriptFiles.push_back(filename);
	}
}