#include "application.hpp"

Application::Application()
{
    
}

Application::~Application()
{
    
}

void Application::onInit()
{
    int size;
    char *buffer;
    
    if (LoadFile("GreatVibes-Regular.ttf", &buffer, size))
    {
        LoadFont(_context, "GreatVibes", buffer, size);
        free(buffer);
    }
}

void Application::onDraw()
{
    float w = _context->screenWidth;
    float h = _context->screenHeight;

    nvgBeginFrame(_context->nvg, w, h, h > w ? w / h : h / w);
    
    const char *text = "Hello, DrawLoop!";
    nvgFontFaceId(_context->nvg, 0);
    nvgFontSize(_context->nvg, 50);
    nvgText(_context->nvg, 50, 50, text, nullptr);
    
    //nvgCircle(_context->nvg, 300, 300, 250);
    //nvgFillColor(_context->nvg, nvgRGBA(55,192,0,255));
    //nvgFill(_context->nvg);
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
