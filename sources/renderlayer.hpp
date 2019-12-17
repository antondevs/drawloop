#ifndef __RENDERLAYER_H
#define __RENDERLAYER_H

#include <map>
#include <vector>
#include <math.h>
#include <string>

extern "C" {
#include "nanovg.h"
#include "nanosvg.h"
}

struct StringComparer
{
    public:
    bool operator()(const std::string x, const std::string y) const
    {
         return x.compare(y)==0;
    }
};

struct RenderContext
{
    void *userData;
    NVGcontext *nvg;
    int screenWidth;
    int screenHeight;
    std::vector<NSVGimage *> svgImages;
    std::map<std::string, int, StringComparer> resources;
    
    RenderContext()
    {
        nvg = nullptr;
        screenWidth = 0;
        screenHeight = 0;
        userData = nullptr;
    }
};

RenderContext *CreateContext();
void CleanContext(RenderContext *context);
void ReleaseContext(RenderContext **context);

int FindResource(RenderContext *context, std::string name);
int LoadFont(RenderContext *context, std::string name, char *buffer, int size);
int LoadImage(RenderContext *context, std::string name, char *buffer, int size);
int LoadSvgImage(RenderContext *context, std::string name, char *buffer, int size, const char* units, float dpi);

NVGcolor ColorFromInt(unsigned int value);
unsigned int ColorToInt(NVGcolor color);
bool ColorFromHex(const char *s, size_t len, NVGcolor *color);
unsigned int ColorToInt(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

#endif
