#ifndef __LAUVGBING_H
#define __LAUVGBING_H

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "nanovg.h"
#include "nanosvg.h"
}

#include "renderlayer.hpp"

// Check count of arguments or throw error
#define LUA_CHECKARGS(state,count) if (lua_gettop(lua) != count) { \
        return luaL_error(state, "%s expecting exactly %d arguments", __FUNCTION__, count);}

// Macros for get context
#define LUA_CONTEXT(state) static_cast<RenderContext*>(lua_getuserdata(state))
// Macros for get int value from stack
#define LUA_GETINT(state,idx) (int)luaL_checknumber(state, idx)
// Macros for get int value from stack
#define LUA_GETSTRING(state,idx) (char *)lua_tostring(state, idx)
// Macros for get float value from stack
#define LUA_GETFLOAT(state,idx) (float)luaL_checknumber(state, idx)
// Macros for get boolean value from stack
#define LUA_GETBOOL(state,idx) (bool)lua_toboolean(state, idx)


// Register lua functions
void registerNanovgInLua(lua_State *lua);

#endif
