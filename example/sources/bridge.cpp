#include <memory>
#include "bridge.h"
#include "application.hpp"

std::unique_ptr<Application> application;

void dlCreateApplication(void)
{
    application = std::unique_ptr<Application>(new Application);
}

void dlDrawFrame(void)
{
    if (application.get())
    {
        application->onDraw();
    }
}

void dlTouchDown(int x, int y)
{
    if (application.get())
    {
        application->onTouchDown(x, y);
    }
}

void dlTouchMove(int x, int y)
{
    if (application.get())
    {
        application->onTouchMove(x, y);
    }
}

void dlTouchUp(int x, int y)
{
    if (application.get())
    {
        application->onTouchUp(x, y);
    }
}

void dlUpdateContext(void *context)
{
    if (application.get())
    {
        application->updateContext(static_cast<NVGcontext*>(context));
    }
}

void dlUpdateSize(int width, int height)
{
    if (application.get())
    {
        application->updateScreenSize(width, height);
    }
}
