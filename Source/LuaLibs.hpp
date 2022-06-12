#pragma once
#include "ScriptComponent.hpp"
#include "Transform.hpp"
#include "Sprite.hpp"

namespace Orion
{
	static int newTransform(lua_State* L)
	{
		auto t = new Transform();
		lua_pushlightuserdata(L, t);
		t->GetScale()[0] = 4;
		return 1;
	}

	static int setpos(lua_State* L)
	{
		Transform* t = (Transform*)(lua_touserdata(L, 1));
		t->GetRotation() = lua_tonumber(L, 2);
		t->GetTranslation()[0] = sin(lua_tonumber(L, 2));
		t->GetTranslation()[1] = sin(lua_tonumber(L, 3));
		return 0;
	}

	const luaL_Reg transformLib[] =
	{
		{"new", newTransform},
		{"set", setpos}
	};


	class LuaLib
	{
	public:
		LuaLib();
		LuaLib(const luaL_Reg* funcs, int nfuncs);
		void Add(luaL_Reg func);
		void Open(lua_State* L, std::string name);
	private:
		std::list<luaL_Reg> m_funcs;
	};
}