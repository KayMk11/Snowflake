#pragma once
#include "application/input.h"

namespace Snowflake
{
    class inputGLFW : public Input
    {
    protected:
        virtual bool isKeyPressedImpl(int keyCode) override
        {
            auto *window = static_cast<GLFWwindow* > (Application::get()->getApplicationWindow()->getNativeWindow());
            auto state = glfwGetKey(window, keyCode);
            return state == GLFW_PRESS;
        }

        virtual bool isMouseButtonPressedImpl(int keyCode) override
        {
            auto *window = static_cast<GLFWwindow* > (Application::get()->getApplicationWindow()->getNativeWindow());
            auto state = glfwGetMouseButton(window, keyCode);
            return state == GLFW_PRESS;
        }

        virtual glm::vec2 getMousePositionImpl() override
        {
            auto *window = static_cast<GLFWwindow* > (Application::get()->getApplicationWindow()->getNativeWindow());
            double xPos, yPos;
            glfwGetCursorPos(window,&xPos, &yPos);
            
            return {(float) xPos, (float) yPos};
        }
        
        virtual float getMouseXImpl() override
        {
            return getMousePosition().x;
        }

        virtual float getMouseYImpl() override
        {
            return getMousePosition().y;
        }

    };
    Input* Input::instance = new inputGLFW();
} // namespace Snowflake
