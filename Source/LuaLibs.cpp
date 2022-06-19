#include "LuaLibs.hpp"

namespace Orion
{
	LuaLib::LuaLib()
	{
		luaL_Reg nullfunc = { NULL, NULL };
		Add(nullfunc);
	}

	LuaLib::LuaLib(const luaL_Reg* funcs, int nfuncs)
	{
		for (int i = 0; i < nfuncs; ++i)
		{
			Add(funcs[i]);
		}
		m_funcs.push_back({ NULL, NULL });
	}

	void LuaLib::Add(luaL_Reg func)
	{
		m_funcs.push_front(func);
	}

	void LuaLib::Open(lua_State* L, std::string name)
	{
		std::vector<luaL_Reg> funcs;
		for (auto f : m_funcs)
		{
			funcs.push_back(f);
		}
		lua_newtable(L);
		luaL_setfuncs(L, funcs.data(), 0);
		lua_setglobal(L, name.c_str());
	}
}