#pragma once
#include "ScriptComponent.hpp"
#include "Transform.hpp"
#include "Sprite.hpp"
#include "Input.hpp"

namespace Orion
{
	static int transform_new(lua_State* L)
	{
		auto t = new Transform();
		lua_pushlightuserdata(L, t);
		return 1;
	}

	static int transform_setPos(lua_State* L)
	{
		Transform* t = (Transform*)(lua_touserdata(L, 1));
		t->GetRotation() = lua_tonumber(L, 2);
		t->GetTranslation()[0] = lua_tonumber(L, 2);
		t->GetTranslation()[1] = lua_tonumber(L, 3);
		return 0;
	}

	static int sprite_new(lua_State* L)
	{
		auto t = new Sprite();
		lua_pushlightuserdata(L, t);
		return 1;
	}

	static int sprite_setColor(lua_State* L)
	{
		Sprite* s = (Sprite*)(lua_touserdata(L, 1));
		s->GetColor()[0] = sin(lua_tonumber(L, 2));
		s->GetColor()[1] = sin(lua_tonumber(L, 3));
		s->GetColor()[2] = sin(lua_tonumber(L, 4));
		return 0;
	}

	static int input_isPressed(lua_State* L)
	{
		int keyCode = lua_tonumber(L, 1);
		lua_pushboolean(L, Input::isPressed(keyCode));
		return 1;
	}

	static int input_isHeld(lua_State* L)
	{
		int keyCode = lua_tonumber(L, 1);
		lua_pushboolean(L, Input::isHeld(keyCode));
		return 1;
	}

	static int input_isReleased(lua_State* L)
	{
		int keyCode = lua_tonumber(L, 1);
		lua_pushboolean(L, Input::isReleased(keyCode));
		return 1;
	}

	const luaL_Reg transformLib[] =
	{
		{"new", transform_new},
		{"setPos", transform_setPos}
	};

	const luaL_Reg spriteLib[] =
	{
		{"new", sprite_new},
		{"setColor", sprite_setColor}
	};

	const luaL_Reg inputLib[] =
	{
		{"isPressed", input_isPressed},
		{"isHeld", input_isHeld},
		{"isReleased", input_isReleased}
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