#pragma once
#include <glm/glm.hpp>
#include "application.h"

namespace Snowflake
{
    class Input
    {
        static Input* instance;

    protected:
        virtual bool isKeyPressedImpl(int keyCode) = 0;
        virtual bool isMouseButtonPressedImpl(int keyCode) = 0;
        virtual glm::vec2 getMousePositionImpl() = 0;
        virtual float getMouseXImpl() = 0;
        virtual float getMouseYImpl() = 0;

    public:
        static inline bool isKeyPressed(int keyCode) { return instance->isKeyPressedImpl(keyCode); };
        static inline bool isMouseButtonPressed(int keyCode) { return instance->isMouseButtonPressedImpl(keyCode); };
        static inline glm::vec2 getMousePosition() { return instance->getMousePositionImpl(); };
        static inline float getMouseX() { return instance->getMouseX(); };
        static inline float getMouseY() { return instance->getMouseY(); };
    };
    // Input* Input::instance = nullptr;

} // namespace Snowflake
