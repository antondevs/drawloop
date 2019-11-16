#include "luavgbind.hpp"

// HELPERS

void lua_pushpaint(lua_State *lua, NVGpaint *paint) {
    NVGpaint **pointer = reinterpret_cast<NVGpaint **>(lua_newuserdata(lua, sizeof(NVGpaint*)));
    *pointer = paint;
}

// CONTROL RENDERING

// Begin drawing a new frame
int nvg_beginFrame(lua_State *lua) {
    LUA_CHECKARGS(lua, 3);
    auto context = LUA_CONTEXT(lua);
    nvgBeginFrame(context->nvg, LUA_GETFLOAT(lua, 1), LUA_GETFLOAT(lua, 2), LUA_GETFLOAT(lua, 3));
    return 0;
}

// Cancels drawing the current frame
int nvg_cancelFrame(lua_State *lua) {
    LUA_CHECKARGS(lua, 0);
    auto context = LUA_CONTEXT(lua);
    nvgCancelFrame(context->nvg);
    return 0;
}

// Ends drawing flushing remaining render state
int nvg_endFrame(lua_State *lua) {
    LUA_CHECKARGS(lua, 0);
    auto context = LUA_CONTEXT(lua);
    nvgEndFrame(context->nvg);
    return 0;
}

// COMPOSITE OPERATION

// Sets the composite operation. The op parameter should be one of NVGcompositeOperation.
int nvg_globalCompositeOperation(lua_State *lua) {
    LUA_CHECKARGS(lua, 1);
    auto context = LUA_CONTEXT(lua);
    const char* options[] = {
        "SOURCE_OVER", "SOURCE_IN", "SOURCE_OUT", "ATOP", "DESTINATION_OVER",
        "DESTINATION_IN", "DESTINATION_OUT", "DESTINATION_ATOP", "LIGHTER", "COPY", "XOR"
    };
    const NVGcompositeOperation values[] =
    {
        NVG_SOURCE_OVER, NVG_SOURCE_IN, NVG_SOURCE_OUT, NVG_ATOP, NVG_DESTINATION_OVER, NVG_DESTINATION_IN,
        NVG_DESTINATION_OUT, NVG_DESTINATION_ATOP, NVG_LIGHTER, NVG_COPY, NVG_XOR
    };
    nvgGlobalCompositeOperation(context->nvg, values[luaL_checkoption(lua, 1, nullptr, options)]);
    return 0;
}

// Sets the composite operation with custom pixel arithmetic
int nvg_globalCompositeBlendFunc(lua_State *lua) {
    LUA_CHECKARGS(lua, 2);
    auto context = LUA_CONTEXT(lua);
    const char* options[] = {
        "ZERO", "ONE", "SRC_COLOR", "ONE_MINUS_SRC_COLOR", "DST_COLOR", "ONE_MINUS_DST_COLOR",
        "SRC_ALPHA", "ONE_MINUS_SRC_ALPHA", "DST_ALPHA", "ONE_MINUS_DST_ALPHA", "SRC_ALPHA_SATURATE"
    };
    const NVGblendFactor values[] =
    {
        NVG_ZERO, NVG_ONE, NVG_SRC_COLOR, NVG_ONE_MINUS_SRC_COLOR, NVG_DST_COLOR, NVG_ONE_MINUS_DST_COLOR,
        NVG_SRC_ALPHA, NVG_ONE_MINUS_SRC_ALPHA, NVG_DST_ALPHA, NVG_ONE_MINUS_DST_ALPHA, NVG_SRC_ALPHA_SATURATE
    };
    auto sfactor = values[luaL_checkoption(lua, 1, nullptr, options)];
    auto dfactor = values[luaL_checkoption(lua, 2, nullptr, options)];
    nvgGlobalCompositeBlendFunc(context->nvg, sfactor, dfactor);
    return 0;
}

// Sets the composite operation with custom pixel arithmetic for RGB and alpha components separately
int nvg_globalCompositeBlendFuncSeparate(lua_State *lua) {
    LUA_CHECKARGS(lua, 4);
    //auto context = LUA_CONTEXT(lua);
    luaL_error(lua, "Not implemented");
    return 0;
}

// COLOR UTILS

// Color from RGB
int nvg_colorFromRGB(lua_State *lua)
{
    LUA_CHECKARGS(lua, 3);
    unsigned int color = ColorToInt(LUA_GETINT(lua, 1), LUA_GETINT(lua, 2), LUA_GETINT(lua, 3), 255);
    lua_pushinteger(lua, color);
    return 1;
}

// Color from RGBA
int nvg_colorFromRGBA(lua_State *lua)
{
    LUA_CHECKARGS(lua, 4);
    unsigned int color = ColorToInt(LUA_GETINT(lua, 1), LUA_GETINT(lua, 2), LUA_GETINT(lua, 3), LUA_GETINT(lua, 4));
    lua_pushinteger(lua, color);
    return 1;
}

// Color from HEX
int nvg_colorFromHEX(lua_State *lua)
{
    LUA_CHECKARGS(lua, 1);
    NVGcolor color;
    char *hexColor = LUA_GETSTRING(lua, 1);
    ColorFromHex(hexColor, strlen(hexColor), &color);
    lua_pushinteger(lua, ColorToInt(color));
    return 1;
}

// Color from HSL
int nvg_colorFromHSL(lua_State *lua)
{
    LUA_CHECKARGS(lua, 3);
    NVGcolor color = nvgHSL(LUA_GETFLOAT(lua, 1), LUA_GETFLOAT(lua, 2), LUA_GETFLOAT(lua, 3));
    lua_pushinteger(lua, ColorToInt(color));
    return 1;
}

// Color from HSLA
int nvg_colorFromHSLA(lua_State *lua)
{
    LUA_CHECKARGS(lua, 4);
    NVGcolor color = nvgHSLA(LUA_GETFLOAT(lua, 1), LUA_GETFLOAT(lua, 2), LUA_GETFLOAT(lua, 3), LUA_GETINT(lua, 4));
    lua_pushinteger(lua, ColorToInt(color));
    return 1;
}

// STATE HANDLING

// A matching nvgRestore() must be used to restore the state
int nvg_save(lua_State *lua)
{
    LUA_CHECKARGS(lua, 0);
    auto context = LUA_CONTEXT(lua);
    nvgSave(context->nvg);
    return 0;
}

// Pops and restores current render state
int nvg_restore(lua_State *lua)
{
    LUA_CHECKARGS(lua, 0);
    auto context = LUA_CONTEXT(lua);
    nvgRestore(context->nvg);
    return 0;
}

// Resets current render state to default values
int nvg_reset(lua_State *lua)
{
    LUA_CHECKARGS(lua, 0);
    auto context = LUA_CONTEXT(lua);
    nvgReset(context->nvg);
    return 0;
}

// RENDER STYLES

// Sets whether to draw antialias for nvgStroke() and nvgFill()
int nvg_shapeAntiAlias(lua_State *lua)
{
    LUA_CHECKARGS(lua, 1);
    auto context = LUA_CONTEXT(lua);
    nvgShapeAntiAlias(context->nvg, LUA_GETBOOL(lua, 1));
    return 0;
}

// Sets current stroke style to a solid color
int nvg_strokeColor(lua_State *lua)
{
    LUA_CHECKARGS(lua, 1);
    auto context = LUA_CONTEXT(lua);
    NVGcolor color = ColorFromInt(LUA_GETINT(lua, 1));
    nvgStrokeColor(context->nvg, color);
    return 0;
}

// Sets current stroke style to a paint, which can be a one of the gradients or a pattern
int nvg_strokePaint(lua_State *lua)
{
    LUA_CHECKARGS(lua, 0);
    auto context = LUA_CONTEXT(lua);
    
    return 0;
}

// Sets current fill style to a solid color
int nvg_fillColor(lua_State *lua)
{
    LUA_CHECKARGS(lua, 1);
    auto context = LUA_CONTEXT(lua);
    NVGcolor color = ColorFromInt(LUA_GETINT(lua, 1));
    nvgFillColor(context->nvg, color);
    return 0;
}

// Sets current fill style to a paint, which can be a one of the gradients or a pattern
int nvg_fillPaint(lua_State *lua)
{
    LUA_CHECKARGS(lua, 0);
    auto context = LUA_CONTEXT(lua);
    
    return 0;
}

// Sets the miter limit of the stroke style
int nvg_miterLimit(lua_State *lua)
{
    LUA_CHECKARGS(lua, 1);
    auto context = LUA_CONTEXT(lua);
    nvgMiterLimit(context->nvg, LUA_GETFLOAT(lua, 1));
    return 0;
}

// Sets the stroke width of the stroke style
int nvg_strokeWidth(lua_State *lua)
{
    LUA_CHECKARGS(lua, 1);
    auto context = LUA_CONTEXT(lua);
    nvgStrokeWidth(context->nvg, LUA_GETFLOAT(lua, 1));
    return 0;
}

// Sets how the end of the line (cap) is drawn, can be one of: NVG_BUTT (default), NVG_ROUND, NVG_SQUARE
int nvg_lineCap(lua_State *lua)
{
    LUA_CHECKARGS(lua, 1);
    auto context = LUA_CONTEXT(lua);
    const char* options[] = { "BUTT", "ROUND", "SQUARE"};
    const NVGlineCap values[] = { NVG_BUTT, NVG_ROUND, NVG_SQUARE };
    nvgLineCap(context->nvg, values[luaL_checkoption(lua, 1, nullptr, options)]);
    return 0;
}

int nvg_lineJoin(lua_State *lua)
{
    LUA_CHECKARGS(lua, 1);
    auto context = LUA_CONTEXT(lua);
    const char* options[] = { "MITER", "ROUND", "BEVEL"};
    const NVGlineCap values[] = { NVG_MITER, NVG_ROUND, NVG_BEVEL };
    nvgLineJoin(context->nvg, values[luaL_checkoption(lua, 1, nullptr, options)]);
    return 0;
}

int nvg_globalAlpha(lua_State *lua)
{
    LUA_CHECKARGS(lua, 1);
    auto context = LUA_CONTEXT(lua);
    nvgGlobalAlpha(context->nvg, LUA_GETFLOAT(lua, 1));
    return 0;
}

// TRANSFORMS

// Resets current transform to a identity matrix
int nvg_resetTransform(lua_State *lua)
{
    LUA_CHECKARGS(lua, 0);
    auto context = LUA_CONTEXT(lua);
    nvgResetTransform(context->nvg);
    return 0;
}

// Premultiplies current coordinate system by specified matrix
int nvg_transform(lua_State *lua)
{
    LUA_CHECKARGS(lua, 6);
    auto context = LUA_CONTEXT(lua);
    nvgTransform(context->nvg, LUA_GETFLOAT(lua, 1), LUA_GETFLOAT(lua, 2), LUA_GETFLOAT(lua, 3),
                 LUA_GETFLOAT(lua, 4), LUA_GETFLOAT(lua, 5), LUA_GETFLOAT(lua, 6));
    return 0;
}

int nvg_translate(lua_State *lua)
{
    LUA_CHECKARGS(lua, 2);
    auto context = LUA_CONTEXT(lua);
    nvgTranslate(context->nvg, LUA_GETFLOAT(lua, 1), LUA_GETFLOAT(lua, 2));
    return 0;
}

int nvg_rotate(lua_State *lua)
{
    LUA_CHECKARGS(lua, 1);
    auto context = LUA_CONTEXT(lua);
    nvgRotate(context->nvg, LUA_GETFLOAT(lua, 1));
    return 0;
}

int nvg_skewX(lua_State *lua)
{
    LUA_CHECKARGS(lua, 1);
    auto context = LUA_CONTEXT(lua);
    nvgSkewX(context->nvg, LUA_GETFLOAT(lua, 1));
    return 0;
}

int nvg_skewY(lua_State *lua)
{
    LUA_CHECKARGS(lua, 1);
    auto context = LUA_CONTEXT(lua);
    nvgSkewY(context->nvg, LUA_GETFLOAT(lua, 1));
    return 0;
}

int nvg_scale(lua_State *lua)
{
    LUA_CHECKARGS(lua, 2);
    auto context = LUA_CONTEXT(lua);
    nvgScale(context->nvg, LUA_GETFLOAT(lua, 1), LUA_GETFLOAT(lua, 2));
    return 0;
}

int nvg_currentTransform(lua_State *lua)
{
    LUA_CHECKARGS(lua, 0);
    auto context = LUA_CONTEXT(lua);
    float* matrix = (float*) lua_newuserdata(lua, sizeof(float) * 6);
    nvgCurrentTransform(context->nvg, matrix);
    return 0;
}

int nvg_createMatrix(lua_State *lua)
{
    LUA_CHECKARGS(lua, 0);
    float* matrix = (float*) lua_newuserdata(lua, sizeof(float) * 6);
    memset(matrix, 0, sizeof(float) * 6);
    return 0;
}

int nvg_transformIdentity(lua_State *lua)
{
    LUA_CHECKARGS(lua, 1);
    float* matrix = (float*) lua_touserdata(lua, 1);
    nvgTransformIdentity(matrix);
    return 0;
}

int nvg_transformTranslate(lua_State *lua)
{
    LUA_CHECKARGS(lua, 3);
    float* matrix = (float*) lua_touserdata(lua, 1);
    nvgTransformTranslate(matrix, LUA_GETFLOAT(lua, 1), LUA_GETFLOAT(lua, 2));
    return 0;
}

int nvg_transformScale(lua_State *lua)
{
    LUA_CHECKARGS(lua, 3);
    float* matrix = (float*) lua_touserdata(lua, 1);
    nvgTransformScale(matrix, LUA_GETFLOAT(lua, 1), LUA_GETFLOAT(lua, 2));
    return 0;
}

int nvg_transformRotate(lua_State *lua)
{
    LUA_CHECKARGS(lua, 2);
    float* matrix = (float*) lua_touserdata(lua, 1);
    nvgTransformRotate(matrix, LUA_GETFLOAT(lua, 1));
    return 0;
}

int nvg_transformSkewX(lua_State *lua)
{
    LUA_CHECKARGS(lua, 2);
    float* matrix = (float*) lua_touserdata(lua, 1);
    nvgTransformSkewX(matrix, LUA_GETFLOAT(lua, 1));
    return 0;
}

int nvg_transformSkewY(lua_State *lua)
{
    LUA_CHECKARGS(lua, 2);
    float* matrix = (float*) lua_touserdata(lua, 1);
    nvgTransformSkewY(matrix, LUA_GETFLOAT(lua, 1));
    return 0;
}

int nvg_transformMultiply(lua_State *lua)
{
    LUA_CHECKARGS(lua, 2);
    float* matrixDest = (float*) lua_touserdata(lua, 1);
    float* matrixSrc = (float*) lua_touserdata(lua, 1);
    nvgTransformMultiply(matrixDest, matrixSrc);
    return 0;
}

int nvg_transformPremultiply(lua_State *lua)
{
    LUA_CHECKARGS(lua, 2);
    float* matrixDest = (float*) lua_touserdata(lua, 1);
    float* matrixSrc = (float*) lua_touserdata(lua, 1);
    nvgTransformPremultiply(matrixDest, matrixSrc);
    return 0;
}

int nvg_transformInverse(lua_State *lua)
{
    LUA_CHECKARGS(lua, 2);
    float* matrixDest = (float*) lua_touserdata(lua, 1);
    float* matrixSrc = (float*) lua_touserdata(lua, 1);
    nvgTransformInverse(matrixDest, matrixSrc);
    return 0;
}

// Converts degrees to radians and vice versa
int nvg_degToRad(lua_State *lua)
{
    LUA_CHECKARGS(lua, 1);
    lua_pushnumber(lua, nvgDegToRad(LUA_GETFLOAT(lua, 1)));
    return 1;
}

// Converts degrees to radians and vice versa
int nvg_radToDeg(lua_State *lua)
{
    LUA_CHECKARGS(lua, 1);
    lua_pushnumber(lua, nvgRadToDeg(LUA_GETFLOAT(lua, 1)));
    return 1;
}

int nvg_linearGradient(lua_State *lua)
{
    LUA_CHECKARGS(lua, 6);
    auto context = LUA_CONTEXT(lua);
    NVGcolor icol = ColorFromInt(LUA_GETINT(lua, 5));
    NVGcolor ocol = ColorFromInt(LUA_GETINT(lua, 6));
    NVGpaint paint = nvgLinearGradient(context->nvg, LUA_GETFLOAT(lua, 1), LUA_GETFLOAT(lua, 2), LUA_GETFLOAT(lua, 3), LUA_GETFLOAT(lua, 4), icol, ocol);
    lua_pushpaint(lua, &paint);
    return 1;
}

int nvg_boxGradient(lua_State *lua)
{
    LUA_CHECKARGS(lua, 8);
    auto context = LUA_CONTEXT(lua);
    NVGcolor icol = ColorFromInt(LUA_GETINT(lua, 7));
    NVGcolor ocol = ColorFromInt(LUA_GETINT(lua, 8));
    NVGpaint paint = nvgBoxGradient(context->nvg, LUA_GETFLOAT(lua, 1), LUA_GETFLOAT(lua, 2), LUA_GETFLOAT(lua, 3), LUA_GETFLOAT(lua, 4), LUA_GETFLOAT(lua, 5), LUA_GETFLOAT(lua, 6), icol, ocol);
    lua_pushpaint(lua, &paint);
    return 1;
}

int nvg_radialGradient(lua_State *lua)
{
    LUA_CHECKARGS(lua, 6);
    auto context = LUA_CONTEXT(lua);
    NVGcolor icol = ColorFromInt(LUA_GETINT(lua, 5));
    NVGcolor ocol = ColorFromInt(LUA_GETINT(lua, 6));
    NVGpaint paint = nvgRadialGradient(context->nvg, LUA_GETFLOAT(lua, 1), LUA_GETFLOAT(lua, 2), LUA_GETFLOAT(lua, 3), LUA_GETFLOAT(lua, 4), icol, ocol);
    lua_pushpaint(lua, &paint);
    return 1;
}

int nvg_imagePattern(lua_State *lua)
{
    LUA_CHECKARGS(lua, 7);
    auto context = LUA_CONTEXT(lua);
    NVGpaint paint = nvgImagePattern(context->nvg, LUA_GETFLOAT(lua, 1), LUA_GETFLOAT(lua, 2), LUA_GETFLOAT(lua, 3), LUA_GETFLOAT(lua, 4), LUA_GETFLOAT(lua, 5), LUA_GETINT(lua, 6), LUA_GETFLOAT(lua, 7));
    lua_pushpaint(lua, &paint);
    return 1;
}

// SCISSORING

// Intersects current scissor rectangle with the specified rectangle
int nvg_intersectScissor(lua_State *lua)
{
    LUA_CHECKARGS(lua, 4);
    auto context = LUA_CONTEXT(lua);
    nvgIntersectScissor(context->nvg, LUA_GETFLOAT(lua, 1), LUA_GETFLOAT(lua, 2),
               LUA_GETFLOAT(lua, 3), LUA_GETFLOAT(lua, 4));
    return 0;
}

// The scissor rectangle is transformed by the current transform
int nvg_scissor(lua_State *lua)
{
    LUA_CHECKARGS(lua, 4);
    auto context = LUA_CONTEXT(lua);
    nvgScissor(context->nvg, LUA_GETFLOAT(lua, 1), LUA_GETFLOAT(lua, 2),
               LUA_GETFLOAT(lua, 3), LUA_GETFLOAT(lua, 4));
    return 0;
}

// Reset and disables scissoring
int nvg_resetScissor(lua_State *lua)
{
    LUA_CHECKARGS(lua, 0);
    auto context = LUA_CONTEXT(lua);
    nvgResetScissor(context->nvg);
    return 0;
}

// PATHS

// Clears the current path and sub-paths
int nvgBeginPath(lua_State *lua)
{
    LUA_CHECKARGS(lua, 0);
    auto context = LUA_CONTEXT(lua);
    nvgBeginPath(context->nvg);
    return 0;
}

// Starts new sub-path with specified point as first point
int nvgMoveTo(lua_State *lua)
{
    LUA_CHECKARGS(lua, 2);
    auto context = LUA_CONTEXT(lua);
    nvgMoveTo(context->nvg, LUA_GETFLOAT(lua, 1), LUA_GETFLOAT(lua, 2));
    return 0;
}

// Adds line segment from the last point in the path to the specified point
int nvgLineTo(lua_State *lua)
{
    LUA_CHECKARGS(lua, 2);
    auto context = LUA_CONTEXT(lua);
    nvgLineTo(context->nvg, LUA_GETFLOAT(lua, 1), LUA_GETFLOAT(lua, 2));
    return 0;
}

// Adds cubic bezier segment from last point in the path via two control points to the specified point
int nvgBezierTo(lua_State *lua)
{
    LUA_CHECKARGS(lua, 6);
    auto context = LUA_CONTEXT(lua);
    nvgBezierTo(context->nvg, LUA_GETFLOAT(lua, 1), LUA_GETFLOAT(lua, 2), LUA_GETFLOAT(lua, 3), LUA_GETFLOAT(lua, 4), LUA_GETFLOAT(lua, 5), LUA_GETFLOAT(lua, 6));
    return 0;
}

// Adds quadratic bezier segment from last point in the path via a control point to the specified point
int nvgQuadTo(lua_State *lua)
{
    LUA_CHECKARGS(lua, 4);
    auto context = LUA_CONTEXT(lua);
    nvgQuadTo(context->nvg, LUA_GETFLOAT(lua, 1), LUA_GETFLOAT(lua, 2), LUA_GETFLOAT(lua, 3), LUA_GETFLOAT(lua, 4));
    return 0;
}

// Adds an arc segment at the corner defined by the last path point, and two specified points
int nvgArcTo(lua_State *lua)
{
    LUA_CHECKARGS(lua, 5);
    auto context = LUA_CONTEXT(lua);
    nvgArcTo(context->nvg, LUA_GETFLOAT(lua, 1), LUA_GETFLOAT(lua, 2), LUA_GETFLOAT(lua, 3), LUA_GETFLOAT(lua, 4), LUA_GETFLOAT(lua, 5));
    return 0;
}

// Closes current sub-path with a line segment
int nvgClosePath(lua_State *lua)
{
    LUA_CHECKARGS(lua, 0);
    auto context = LUA_CONTEXT(lua);
    nvgClosePath(context->nvg);
    return 0;
}

// Sets the current sub-path winding, see NVGwinding and NVGsolidity
int nvgPathWinding(lua_State *lua)
{
    LUA_CHECKARGS(lua, 1);
    auto context = LUA_CONTEXT(lua);
    const char* options[] = {"CCW", "CW"};
    const NVGwinding values[] = {NVG_CCW, NVG_CW};
    nvgPathWinding(context->nvg, values[luaL_checkoption(lua, 1, nullptr, options)]);
    return 0;
}

// Creates new circle arc shaped sub-path
int nvgArc(lua_State *lua)
{
    LUA_CHECKARGS(lua, 6);
    auto context = LUA_CONTEXT(lua);
    const char* options[] = {"CCW", "CW"};
    const NVGwinding values[] = {NVG_CCW, NVG_CW};
    nvgArc(context->nvg, LUA_GETFLOAT(lua, 1), LUA_GETFLOAT(lua, 2), LUA_GETFLOAT(lua, 3), LUA_GETFLOAT(lua, 4), LUA_GETFLOAT(lua, 5), values[luaL_checkoption(lua, 1, nullptr, options)]);
    return 0;
}

// Creates new rectangle shaped sub-path
int nvgRect(lua_State *lua)
{
    LUA_CHECKARGS(lua, 4);
    auto context = LUA_CONTEXT(lua);
    nvgRect(context->nvg, LUA_GETFLOAT(lua, 1), LUA_GETFLOAT(lua, 2),
           LUA_GETFLOAT(lua, 3), LUA_GETFLOAT(lua, 4));
    return 0;
}

// Creates new rounded rectangle shaped sub-path
int nvgRoundedRect(lua_State *lua)
{
    LUA_CHECKARGS(lua, 5);
    auto context = LUA_CONTEXT(lua);
    nvgRoundedRect(context->nvg, LUA_GETFLOAT(lua, 1), LUA_GETFLOAT(lua, 2),
           LUA_GETFLOAT(lua, 3), LUA_GETFLOAT(lua, 4), LUA_GETFLOAT(lua, 5));
    return 0;
}

// Creates new rounded rectangle shaped sub-path with varying radii for each corner
int nvgRoundedRectVarying(lua_State *lua)
{
    LUA_CHECKARGS(lua, 8);
    auto context = LUA_CONTEXT(lua);
    nvgRoundedRectVarying(context->nvg, LUA_GETFLOAT(lua, 1), LUA_GETFLOAT(lua, 2),
           LUA_GETFLOAT(lua, 3), LUA_GETFLOAT(lua, 4), LUA_GETFLOAT(lua, 5),
           LUA_GETFLOAT(lua, 6), LUA_GETFLOAT(lua, 7), LUA_GETFLOAT(lua, 8));
    return 0;
}

// Creates new ellipse shaped sub-path
int nvgEllipse(lua_State *lua)
{
    LUA_CHECKARGS(lua, 4);
    auto context = LUA_CONTEXT(lua);
    nvgEllipse(context->nvg, LUA_GETFLOAT(lua, 1), LUA_GETFLOAT(lua, 2),
           LUA_GETFLOAT(lua, 3), LUA_GETFLOAT(lua, 4));
    return 0;
}

// Creates new circle shaped sub-path
int nvgCircle(lua_State *lua)
{
    LUA_CHECKARGS(lua, 3);
    auto context = LUA_CONTEXT(lua);
    nvgCircle(context->nvg, LUA_GETFLOAT(lua, 1), LUA_GETFLOAT(lua, 2), LUA_GETFLOAT(lua, 3));
    return 0;
}

// Fills the current path with current fill style
int nvgFill(lua_State *lua)
{
    LUA_CHECKARGS(lua, 0);
    auto context = LUA_CONTEXT(lua);
    nvgFill(context->nvg);
    return 0;
}

// Fills the current path with current stroke style
int nvgStroke(lua_State *lua)
{
    LUA_CHECKARGS(lua, 0);
    auto context = LUA_CONTEXT(lua);
    nvgStroke(context->nvg);
    return 0;
}

// TEXT

// Sets the font size of current text style
int nvgFontSize(lua_State *lua)
{
    LUA_CHECKARGS(lua, 1);
    auto context = LUA_CONTEXT(lua);
    nvgFontSize(context->nvg, LUA_GETFLOAT(lua, 1));
    return 0;
}

// Sets the blur of current text style
int nvgFontBlur(lua_State *lua)
{
    LUA_CHECKARGS(lua, 1);
    auto context = LUA_CONTEXT(lua);
    nvgFontBlur(context->nvg, LUA_GETFLOAT(lua, 1));
    return 0;
}

// Sets the letter spacing of current text style
int nvgTextLetterSpacing(lua_State *lua)
{
    LUA_CHECKARGS(lua, 1);
    auto context = LUA_CONTEXT(lua);
    nvgTextLetterSpacing(context->nvg, LUA_GETFLOAT(lua, 1));
    return 0;
}

// Sets the proportional line height of current text style
int nvgTextLineHeight(lua_State *lua)
{
    LUA_CHECKARGS(lua, 1);
    auto context = LUA_CONTEXT(lua);
    nvgTextLineHeight(context->nvg, LUA_GETFLOAT(lua, 1));
    return 0;
}

// Sets the text align of current text style
int nvgTextAlign(lua_State *lua)
{
    LUA_CHECKARGS(lua, 1);
    auto context = LUA_CONTEXT(lua);
    const char* options[] = {
        "ALIGN_LEFT", "ALIGN_CENTER", "ALIGN_RIGHT", "ALIGN_TOP", "ALIGN_MIDDLE",
        "ALIGN_BOTTOM", "ALIGN_BASELINE"
    };
    const NVGalign values[] =
    {
        NVG_ALIGN_LEFT, NVG_ALIGN_CENTER, NVG_ALIGN_RIGHT, NVG_ALIGN_TOP, NVG_ALIGN_MIDDLE, NVG_ALIGN_BOTTOM,NVG_ALIGN_BASELINE
    };
    nvgTextAlign(context->nvg, values[luaL_checkoption(lua, 1, nullptr, options)]);
    return 0;
}

// Sets the font face based on specified id of current text style
int nvgFontFaceId(lua_State *lua)
{
    LUA_CHECKARGS(lua, 1);
    auto context = LUA_CONTEXT(lua);
    nvgFontFaceId(context->nvg, LUA_GETINT(lua, 1));
    return 0;
}

// Sets the font face based on specified name of current text style
int nvgFontFace(lua_State *lua)
{
    LUA_CHECKARGS(lua, 1);
    auto context = LUA_CONTEXT(lua);
    nvgFontFace(context->nvg, LUA_GETSTRING(lua, 1));
    return 0;
}

// Draws text string at specified location
int nvgText(lua_State *lua)
{
    LUA_CHECKARGS(lua, 3);
    auto context = LUA_CONTEXT(lua);
    const char *text = LUA_GETSTRING(lua, 3);
    nvgText(context->nvg, LUA_GETFLOAT(lua, 1), LUA_GETFLOAT(lua, 2), text, text + strlen(text) - 1);
    return 0;
}

// Draws multi-line text string at specified location wrapped at the specified width
int nvgTextBox(lua_State *lua)
{
    LUA_CHECKARGS(lua, 4);
    auto context = LUA_CONTEXT(lua);
    const char *text = LUA_GETSTRING(lua, 4);
    nvgTextBox(context->nvg, LUA_GETFLOAT(lua, 1), LUA_GETFLOAT(lua, 2), LUA_GETFLOAT(lua, 3), text, text + strlen(text) - 1);
    return 0;
}

// Measures the specified text string
int nvgTextBounds(lua_State *lua)
{
    LUA_CHECKARGS(lua, 0);
    auto context = LUA_CONTEXT(lua);
    //nvgTextBounds
    return 0;
}

// Measures the specified multi-text string
int nvgTextBoxBounds(lua_State *lua)
{
    LUA_CHECKARGS(lua, 0);
    auto context = LUA_CONTEXT(lua);
    //nvgTextBoxBounds
    return 0;
}

// Calculates the glyph x positions of the specified text
int nvgTextGlyphPositions(lua_State *lua)
{
    LUA_CHECKARGS(lua, 0);
    auto context = LUA_CONTEXT(lua);
    //nvgTextGlyphPositions
    return 0;
}

// Returns the vertical metrics based on the current text style
int nvgTextMetrics(lua_State *lua)
{
    LUA_CHECKARGS(lua, 0);
    auto context = LUA_CONTEXT(lua);
    //nvgTextMetrics
    return 0;
}

// Breaks the specified text into lines
int nvgTextBreakLines(lua_State *lua)
{
    LUA_CHECKARGS(lua, 0);
    auto context = LUA_CONTEXT(lua);
    //nvgTextBreakLines
    return 0;
}

void registerNanovgInLua(lua_State *lua)
{
    lua_register(lua, "BeginFrame", nvg_beginFrame);
    lua_register(lua, "CancelFrame", nvg_cancelFrame);
    lua_register(lua, "EndFrame", nvg_endFrame);
    
    lua_register(lua, "SetGlobalCompositeOperation", nvg_globalCompositeOperation);
    lua_register(lua, "SetGlobalCompositeBlendFunc", nvg_globalCompositeBlendFunc);
    lua_register(lua, "SetGlobalCompositeBlendFuncSeparate", nvg_globalCompositeBlendFuncSeparate);
    
    lua_register(lua, "ColorFromRGB", nvg_colorFromRGB);
    lua_register(lua, "ColorFromRGBA", nvg_colorFromRGBA);
    lua_register(lua, "ColorFromHEX", nvg_colorFromHEX);
    lua_register(lua, "ColorFromHSL", nvg_colorFromHSL);
    lua_register(lua, "ColorFromHSLA", nvg_colorFromHSLA);
    
    lua_register(lua, "Save", nvg_save);
    lua_register(lua, "Restore", nvg_restore);
    lua_register(lua, "Reset", nvg_reset);
    
    lua_register(lua, "SetShapeAntiAlias", nvg_shapeAntiAlias);
    lua_register(lua, "SetStrokeColor", nvg_strokeColor);
    lua_register(lua, "SetStrokePaint", nvg_strokePaint);
    lua_register(lua, "SetFillColor", nvg_fillColor);
    lua_register(lua, "SetFillPaint", nvg_fillPaint);
    lua_register(lua, "SetMiterLimit", nvg_miterLimit);
    lua_register(lua, "SetStrokeWidth", nvg_strokeWidth);
    lua_register(lua, "SetLineCap", nvg_lineCap);
    lua_register(lua, "SetLineJoin", nvg_lineJoin);
    lua_register(lua, "SetGlobalAlpha", nvg_globalAlpha);
    
    lua_register(lua, "SetGlobalAlpha", nvg_globalAlpha);
    lua_register(lua, "SetGlobalAlpha", nvg_globalAlpha);
    lua_register(lua, "SetGlobalAlpha", nvg_globalAlpha);
    
    lua_register(lua, "GetCurrentTransform", nvg_currentTransform);
    
    lua_register(lua, "CreateMatrix", nvg_createMatrix);
    lua_register(lua, "TransformIdentity", nvg_transformIdentity);
    lua_register(lua, "TransformTranslate", nvg_transformTranslate);
    lua_register(lua, "TransformScale", nvg_transformScale);
    lua_register(lua, "TransformRotate", nvg_transformRotate);
    lua_register(lua, "TransformSkewX", nvg_transformSkewX);
    lua_register(lua, "TransformSkewY", nvg_transformSkewY);
    lua_register(lua, "TransformMultiply", nvg_transformMultiply);
    lua_register(lua, "TransformPremultiply", nvg_transformPremultiply);
    lua_register(lua, "TransformInverse", nvg_transformInverse);
    
    lua_register(lua, "ConvertRadToDeg", nvg_radToDeg);
    lua_register(lua, "ConvertDegToRad", nvg_degToRad);
    
    lua_register(lua, "CreateImagePattern", nvg_imagePattern);
    lua_register(lua, "CreateRadialGradient", nvg_radialGradient);
    lua_register(lua, "CreateBoxGradient", nvg_boxGradient);
    lua_register(lua, "CreateLinearGradient", nvg_linearGradient);
    
    lua_register(lua, "IntersectScissor", nvg_intersectScissor);
    lua_register(lua, "Scissor", nvg_scissor);
    lua_register(lua, "ResetScissor", nvg_resetScissor);
    
    lua_register(lua, "BeginPath", nvgBeginPath);
    lua_register(lua, "MoveTo", nvgMoveTo);
    lua_register(lua, "LineTo", nvgLineTo);
    lua_register(lua, "BezierTo", nvgBezierTo);
    lua_register(lua, "QuadTo", nvgQuadTo);
    lua_register(lua, "ArcTo", nvgArcTo);
    lua_register(lua, "ClosePath", nvgClosePath);
    lua_register(lua, "PathWinding", nvgPathWinding);
    lua_register(lua, "Arc", nvgArc);
    lua_register(lua, "Rect", nvgRect);
    lua_register(lua, "RoundedRect", nvgRoundedRect);
    lua_register(lua, "RoundedRectVarying", nvgRoundedRectVarying);
    lua_register(lua, "Ellipse", nvgEllipse);
    lua_register(lua, "Circle", nvgCircle);
    lua_register(lua, "Fill", nvgFill);
    lua_register(lua, "Stroke", nvgStroke);
    
    lua_register(lua, "SetFontSize", nvgFontSize);
    lua_register(lua, "SetFontBlue", nvgFontBlur);
    lua_register(lua, "SetTextLetterSpacing", nvgTextLetterSpacing);
    lua_register(lua, "SetTextLineHeight", nvgTextLineHeight);
    lua_register(lua, "SetTextAlign", nvgTextAlign);
    lua_register(lua, "SetFont", nvgFontFaceId);
    lua_register(lua, "SetFontByName", nvgFontFace);
    lua_register(lua, "DrawText", nvgText);
    lua_register(lua, "DrawTextBox", nvgTextBox);
    lua_register(lua, "GetTextBounds", nvgTextBounds);
    lua_register(lua, "GetTextBoxBounds", nvgTextBoxBounds);
    lua_register(lua, "GetTextGlyphPositions", nvgTextGlyphPositions);
    lua_register(lua, "GetTextMetrics", nvgTextMetrics);
    lua_register(lua, "GetTextBreakLines", nvgTextBreakLines);

}
