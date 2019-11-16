#include "engine.hpp"

Engine::Engine()
{
    _lua = nullptr;
    _context = nullptr;
}

Engine::~Engine()
{
    if (_lua)
    {
        lua_close(_lua);
        _lua = nullptr;
    }
    
    delete _context;
}

void Engine::makeNewLuaState()
{
    if (_lua)
    {
        lua_close(_lua);
        _lua = nullptr;
    }
    
    _lua = luaL_newstate();
    luaL_openlibs(_lua);
    registerNanovgInLua(_lua);
    lua_setuserdata(_lua, _context);
    
    onLuaInit();
}

void Engine::onInit()
{
    _context = new RenderContext();
}

void Engine::onDraw()
{
    
}

void Engine::onLuaInit()
{
    
}

void Engine::onTouchDown(int x, int y)
{
    
}

void Engine::onTouchMove(int x, int y)
{
    
}

void Engine::onTouchUp(int x, int y)
{
    
}

void Engine::updateContext(NVGcontext *nvgContext)
{
    _context->nvg = nvgContext;
}

void Engine::updateScreenSize(int width, int height)
{
    _context->screenWidth = width;
    _context->screenHeight = height;
}

bool Engine::runScript(const char *method)
{
    if (!_lua)
    {
        return false;
    }
    
    if (method)
    {
        lua_getglobal(_lua, method);
    }
    
    if (lua_pcall(_lua, 0, 0, 0))
    {
        const char* err = lua_tostring(_lua, -1);
        Log("Lua error: %s", err);
        return false;
    }
    
    return true;
}

bool Engine::loadScript(const char *data, int size, const char *name)
{
    makeNewLuaState();
    
    if (luaL_loadbufferx(_lua, data, size, name, nullptr) != LUA_OK)
    {
        return false;
    }
    
    return runScript(nullptr);
}

bool Engine::loadScript(const char *filePath)
{
    int size;
    char *buffer;
    
    if (LoadFile(filePath, &buffer, size))
    {
        bool res = loadScript(buffer, size, "main");
        free(buffer);
        return res;
    }
    
    return false;
}
