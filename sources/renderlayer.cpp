#include "renderlayer.hpp"

RenderContext *CreateContext()
{
    return new RenderContext();
}

void CleanContext(RenderContext **context)
{
    if (*context)
    {
        
        delete *context;
        *context = nullptr;
    }
}

void ReleaseContext(RenderContext **context)
{
    if (*context)
    {
        
        delete *context;
        *context = nullptr;
    }
}

int FindResource(RenderContext *context, std::string name)
{
    if (context->resources.count(name))
    {
        return context->resources[name];
    }
    
    return -1;
}

int LoadFont(RenderContext *context, std::string name, char *buffer, int size)
{
    int resId = nvgCreateImageMem(context->nvg, 0, (unsigned char *) buffer, size);
    context->resources.insert(std::make_pair(name, resId));
    return resId;
}

int LoadImage(RenderContext *context, std::string name, char *buffer, int size)
{
    int resId = nvgCreateFontMem(context->nvg, 0, (unsigned char *) buffer, size, 1);
    context->resources.insert(std::make_pair(name, resId));
    return resId;
}

int LoadSvgImage(RenderContext *context, std::string name, char *buffer, int size, const char* units, float dpi)
{
    int resId = (int) context->svgImages.size();
    NSVGimage *image = nsvgParseFromFile(buffer, units, dpi);
    context->svgImages.push_back(image);
    context->resources.insert(std::make_pair(name, resId));
    return resId;
}

NVGcolor ColorFromInt(unsigned int value) {
    NVGcolor color;
    color.a = ((value >> 24) & 0xFF)/255.0f;
    color.r = ((value >> 16) & 0xFF)/255.0f;
    color.g = ((value >>  8) & 0xFF)/255.0f;
    color.b = ((value      ) & 0xFF)/255.0f;
    return color;
}

unsigned int ColorToInt(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    return
        (a << 24) | (r << 16) | (g << 8) | (b);
}

unsigned int ColorToInt(NVGcolor color) {
    return
        ((int)(color.a * 255) << 24) |
        ((int)(color.r * 255) << 16) |
        ((int)(color.g * 255) <<  8) |
        ((int)(color.b * 255)      ) ;
}

const char *SkipWhitespace(const char *s) {
    while (*s == '\t' || *s == '\n' || *s == '\r' || *s == ' ')
        ++s;
    return s;
}

const char *ParseHexadigit(const char *s, unsigned *pv) {
    *pv = 0;
    while ((*s >= '0' && *s <= '9') ||
            (*s >= 'A' && *s <= 'F') ||
            (*s >= 'a' && *s <= 'f')) {
        int ch = *s;
        if (ch <= '9')
            ch -= '0';
        else if (ch <= 'F')
            ch -= 'A' - 10;
        else
            ch -= 'a' - 10;
        *pv = (*pv << 4) | ch;
        ++s;
    }
    return s;
}

bool ColorFromHex(const char *s, size_t len, NVGcolor *color) {
    const char *e;
    unsigned v, packed = 0;
    s = SkipWhitespace(s);
    
    if (*s++ != '#') return false;
    e = ParseHexadigit(s, &v);
    e = SkipWhitespace(e);
    if (*e != '\0') return false;
    if (len == 4 || len == 5) {
        packed = len == 4 ? 0xFF000000 :
            ((v>>8)&0xF0)|((v>>12)&0xF) << 24;
        packed |=
            ((v>>4)&0xF0)|((v>>8)&0xF) << 16 |
            ((v   )&0xF0)|((v>>4)&0xF) <<  8 |
            ((v<<4)&0xF0)|((v   )&0xF)       ;
    }
    else if (len == 7 || len == 9) {
        packed = v;
        if (len == 7)
            packed |= 0xFF000000;
    }
    *color = ColorFromInt(packed);
    return true;
}
