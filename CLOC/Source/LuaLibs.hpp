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
		t->GetTranslation()[0] = lua_tonumber(L, 2);
		t->GetTranslation()[1] = lua_tonumber(L, 3);
		return 0;
	}

	static int transform_getCoord(lua_State* L)
	{
		Transform* t = (Transform*)(lua_touserdata(L, 1));
		int coord = lua_tonumber(L, 2);
		lua_pushinteger(L, t->GetTranslation()[coord]);
		return 1;
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
	static int input_isZPressed(lua_State* L)
	{
		lua_pushboolean(L, Input::isPressed(GLFW_KEY_Z));
		return 1;
	}
	static int input_isXPressed(lua_State* L)
	{
		lua_pushboolean(L, Input::isPressed(GLFW_KEY_X));
		return 1;
	}
	static int input_isCPressed(lua_State * L)
	{
		lua_pushboolean(L, Input::isPressed(GLFW_KEY_C));
		return 1;
	}
	static int input_isRPressed(lua_State * L)
	{
		lua_pushboolean(L, Input::isPressed(GLFW_KEY_RIGHT) || Input::isHeld(GLFW_KEY_RIGHT));
		return 1;
	}
	static int input_isLPressed(lua_State * L)
	{
		lua_pushboolean(L, Input::isPressed(GLFW_KEY_LEFT) || Input::isHeld(GLFW_KEY_LEFT));
		return 1;
	}
	static int input_isDPressed(lua_State* L)
	{
		lua_pushboolean(L, Input::isPressed(GLFW_KEY_DOWN) || Input::isHeld(GLFW_KEY_DOWN));
		return 1;
	}
	static int input_isUPressed(lua_State* L)
	{
		lua_pushboolean(L, Input::isPressed(GLFW_KEY_UP) || Input::isHeld(GLFW_KEY_UP));
		return 1;
	}

	const luaL_Reg transformLib[] =
	{
		{"new", transform_new},
		{"setPos", transform_setPos},
		{"getCoord", transform_getCoord}
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
		{"isReleased", input_isReleased},
		{"isAPressed", input_isZPressed},
		{"isBPressed", input_isXPressed},
		{"isEnterPressed", input_isCPressed},
		{"isUpDown", input_isUPressed},
		{"isLeftDown", input_isLPressed},
		{"isDownDown", input_isDPressed},
		{"isRightDown", input_isRPressed}
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