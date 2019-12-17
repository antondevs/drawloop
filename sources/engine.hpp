#ifndef __ENGINE_H
#define __ENGINE_H

#include "utils.hpp"
#include "renderlayer.hpp"

class Engine
{
protected:
    RenderContext *_context;
    
public:
    Engine();
	~Engine();
	
    virtual void onInit();
    virtual void onDraw();
    virtual void onTouchDown(int x, int y);
    virtual void onTouchMove(int x, int y);
    virtual void onTouchUp(int x, int y);
    
    void updateScreenSize(int width, int height);
    void updateContext(NVGcontext *nvgContext);
};


#endif
