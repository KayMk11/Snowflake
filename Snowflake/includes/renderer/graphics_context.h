#pragma once

#include "core/core.h"
#include "renderer.h"

namespace Snowflake
{   
    class GraphicsContext
    {
        public:
        
        virtual void init() = 0;
        virtual void SwapBuffers() = 0;
        static std::unique_ptr<GraphicsContext> create(void* window);
    };

    class OpenGLContext : public GraphicsContext
    {
        GLFWwindow* window;

    public:
        OpenGLContext(GLFWwindow* windowHandle): window(windowHandle) {}

        virtual void init()
        {
            glfwMakeContextCurrent(window);
            gladLoadGL();
        }

        virtual void SwapBuffers()
        {
            glfwSwapBuffers(window);
        }
    };

    // TODO Move to CPP file?

    std::unique_ptr<GraphicsContext> GraphicsContext::create(void* window)
    {
        switch (Renderer::getAPI())
        {
        case GraphicsAPI::OpenGL:
            return std::unique_ptr<OpenGLContext>(new OpenGLContext(static_cast<GLFWwindow*>(window)));
        case GraphicsAPI::None:
            SF_LOGE("GraphicsAPI None is not supported!");
        
        }
        return nullptr;
    }

} // namespace Snowflake
