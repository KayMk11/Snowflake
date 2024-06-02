#pragma once
#include "core/core.h"

namespace Snowflake
{
    enum class RendererFlags
    {
        DEPTH_TEST,
        STENCIL_TEST,
        BLEND,
        COLOR,
        DEPTH,
    };
    enum class DrawModeFlag
    {
        LINE,
        FILL
    };

    class RendererCommand
    {
    public:
        virtual void execute() = 0;
    };

    class DrawCommand : public RendererCommand
    {
    public:
        virtual void execute()
        {
            // towards GLAPI
        }
    };

    class SetDrawModeCommand : public RendererCommand
    {
        DrawModeFlag mFlag;

    public:
        SetDrawModeCommand(DrawModeFlag flag) : mFlag(flag) {}
        virtual void execute()
        {
            // towards GLAPI
        }
    };
    class ClearCommand : public RendererCommand
    {

    public:
        virtual void execute()
        {
            // towards GLAPI
        }
    };

    class SetDrawModeCommand : public RendererCommand
    {
    public:
        virtual void execute()
        {
            // towards GLAPI
        }
    };

} // namespace Snowflake
