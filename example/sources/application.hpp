#ifndef __APPLICATION_H
#define __APPLICATION_H

#include <math.h>
#include "engine.hpp"

class Application : public Engine
{
private:
    
public:
    Application();
    ~Application();
    
    void onInit() override;
    void onDraw() override;
    void onTouchDown(int x, int y) override;
    void onTouchMove(int x, int y) override;
    void onTouchUp(int x, int y) override;
};

#endif
