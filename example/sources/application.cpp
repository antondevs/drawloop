#include "application.hpp"

Application::Application()
{
    
}

Application::~Application()
{
    
}

void Application::onInit()
{
    Engine::onInit();
    
    int size;
    char *buffer;
    
    if (LoadFile("main.lua", &buffer, size))
    {
        bool res = loadScript(buffer, size, "main");
        free(buffer);
    }
}

void Application::onDraw()
{
    float w = _context->screenWidth;
    float h = _context->screenHeight;

    nvgBeginFrame(_context->nvg, w, h, h > w ? w / h : h / w);
    runScript("main");
    
   // nvgFillColor(_context->nvg, nvgRGBA(55,192,0,255));
//    nvgFill(_context->nvg);
    nvgEndFrame(_context->nvg);
}

void Application::onTouchDown(int x, int y)
{
    
}

void Application::onTouchMove(int x, int y)
{
    
}

void Application::onTouchUp(int x, int y)
{
    
}
