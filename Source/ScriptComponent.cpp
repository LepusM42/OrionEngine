/*!*****************************************************************************
* \file Example.cpp
* \author Lepus
* \brief This is a template for other component files.
*******************************************************************************/
#include "ScriptComponent.hpp"
#include "Transform.hpp"
#include "Sprite.hpp"
#include "Entity.hpp"
#include "LuaLibs.hpp"

namespace Orion
{

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
		for (auto script : m_scripts)
		{
			script.Update();
		}
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
		m_transform = m_parent->Get<Transform>();
		m_sprite = m_parent->Get<Sprite>();
		//Begin execution of all scripts
		for (auto script : m_scripts)
		{
			script.Start();
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
		for (auto script : m_scripts)
		{
			script.Stop();
		}
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
		Script s(filename, this);
		m_scripts.push_back(s);
	}

	/*!*************************************************************************
	* \fn
	* \brief Constructor. Called only once, making it good for one-time initial
	*  allocations.
	* \param
	* \return
	***************************************************************************/
	Transform* ScriptComponent::GetTransform()
	{
		return m_transform;
	}

	/*!*************************************************************************
	* \fn
	* \brief Constructor. Called only once, making it good for one-time initial
	*  allocations.
	* \param
	* \return
	***************************************************************************/
	Sprite* ScriptComponent::GetSprite()
	{
		return m_sprite;
	}

	/*!*************************************************************************
	* \fn
	* \brief Constructor. Called only once, making it good for one-time initial
	*  allocations.
	* \param
	* \return
	***************************************************************************/
	Script::Script(std::string filename, ScriptComponent* parent) :
		m_filename{ filename },
		m_parent{ parent }
	{
		m_luaState = luaL_newstate();
		luaL_openlibs(m_luaState);
	}

	/*!*************************************************************************
	* \fn
	* \brief Constructor. Called only once, making it good for one-time initial
	*  allocations.
	* \param
	* \return
	***************************************************************************/
	void Script::Start()
	{
		std::cout << "Running " << m_filename << "\n";

		//Open transform operation function array library
		LuaLib tLib(transformLib, 2);
		tLib.Open(m_luaState, "transform");

		if (Validate(luaL_dofile(m_luaState, m_filename.c_str())))
		{
			CallLua("Start");
		}

		//Create some userdata using the parent's existing components
		CreateUserData(m_parent->GetTransform(), "playerTransform");
		CreateUserData(m_parent->GetSprite(), "playerSprite");
	}

	/*!*************************************************************************
	* \fn
	* \brief Constructor. Called only once, making it good for one-time initial
	*  allocations.
	* \param
	* \return
	***************************************************************************/
	void Script::Update()
	{
		if (Validate(luaL_dofile(m_luaState, m_filename.c_str())))
		{
			CallLua("Update");
		}
	}

	/*!*************************************************************************
	* \fn
	* \brief Constructor. Called only once, making it good for one-time initial
	*  allocations.
	* \param
	* \return
	***************************************************************************/
	int Script::DoString(std::string string)
	{
		std::cout << "Running " << string << "\n";
		Validate(luaL_dostring(m_luaState, string.c_str()));
		return 0;
	}

	/*!*************************************************************************
	* \fn
	* \brief Constructor. Called only once, making it good for one-time initial
	*  allocations.
	* \param
	* \return
	***************************************************************************/
	int Script::DoFile(std::string filename)
	{
		std::cout << "Running " << filename << "\n";
		Validate(luaL_dofile(m_luaState, filename.c_str()));
		return 0;
	}

	/*!*************************************************************************
	* \fn
	* \brief Constructor. Called only once, making it good for one-time initial
	*  allocations.
	* \param
	* \return
	***************************************************************************/
	int Script::CallLua(std::string funcName)
	{
		lua_getglobal(m_luaState, funcName.c_str());
		if (lua_isfunction(m_luaState, -1))
		{
			Validate(lua_pcall(m_luaState, 0, 0, 0));
		}
		return 0;
	}

	/*!*************************************************************************
	* \fn
	* \brief Constructor. Called only once, making it good for one-time initial
	*  allocations.
	* \param
	* \return
	***************************************************************************/
	bool Script::Validate(int result)
	{
		if (result == LUA_OK)
		{
			return true;
		}
		else
		{
			std::cout << "LUA operation unsuccessful.\n";
			std::cout << lua_tostring(m_luaState, -1) << "\n";
			lua_pop(m_luaState, 1);
			return false;
		}
	}

	/*!*************************************************************************
	* \fn
	* \brief Constructor. Called only once, making it good for one-time initial
	*  allocations.
	* \param
	* \return
	***************************************************************************/
	void Script::Stop()
	{
		lua_close(m_luaState);
	}

}