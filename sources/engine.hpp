#ifndef __ENGINE_H
#define __ENGINE_H

#include "utils.hpp"
#include "luavgbind.hpp"

class Engine
{
protected:
    lua_State *_lua;
    RenderContext *_context;
    void makeNewLuaState();
    
public:
    Engine();
	~Engine();
	
    virtual void onInit();
    virtual void onDraw();
    virtual void onLuaInit();
    virtual void onTouchDown(int x, int y);
    virtual void onTouchMove(int x, int y);
    virtual void onTouchUp(int x, int y);
    
    void updateScreenSize(int width, int height);
    void updateContext(NVGcontext *nvgContext);
    
    bool loadScript(const char *filePath);
    bool loadScript(const char *data, int size, const char *name = nullptr);
    bool runScript(const char *method);
};


#endif
