#include "engine.hpp"

Engine::Engine()
{
    _context = new RenderContext();
}

Engine::~Engine()
{
    delete _context;
}

void Engine::onInit()
{
    
}

void Engine::onDraw()
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
    onInit();
}

void Engine::updateScreenSize(int width, int height)
{
    _context->screenWidth = width;
    _context->screenHeight = height;
}
