#pragma once

#include "core/core.h"

namespace Snowflake
{
    enum class ComponentType 
    {
        RENDERABLE,
        NONE
    };

    class Component
    {
    protected:
        ComponentType mType;
    public:
        Component(ComponentType type) : mType(type) {}
        ~Component() {}
    };
} // namespace Snowflake
