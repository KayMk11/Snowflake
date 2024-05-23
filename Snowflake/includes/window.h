#pragma once
// #include "core.h"
#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "graphics_context.h"
namespace Snowflake
{

    static void GLFWErrorCallback(int error, const char* description)
	{
		SF_LOGE("GLFW Error %d : %s", error, description);
	}

    class Window : public EventConsumer
    {
    protected:
        int height, width;
        std::string title;

    public:
        Window(int height = 1280, int width = 800, std::string title = "Snowflake") : height(height),
                                                                                      width(width),
                                                                                      title(title){};

        virtual void updateWindow() = 0;
        virtual void shutdown() = 0;
        virtual void *getNativeWindow() = 0;
    };

    class WindowGLFW : public Window
    {

        GLFWwindow *nativeWindow;
        std::unique_ptr<GraphicsContext> context;
    public:
        WindowGLFW(int height = 1280, int width = 800, std::string title = "Snowflake") : Window(height, width, title)
        {
            // TODO add support for multiple windows-----------------------
            if (!glfwInit())
            {
                SF_LOGE("GLFW Initialization failed !!");
                return;
            }
            glfwSetErrorCallback(GLFWErrorCallback);
            // TODO add support for multiple windows-----------------------
            nativeWindow = glfwCreateWindow(height, width, title.c_str(), NULL, NULL);

            if (!nativeWindow)
            {
                SF_LOGE("GLFW window creation failed !!");
                // glfwTerminate();
                return;
            }
            context = GraphicsContext::create(nativeWindow);
            context->init();

            // Set Callbacks
            glfwSetFramebufferSizeCallback(nativeWindow, [](GLFWwindow *window, int width, int height)
            { 
                WindowResizeEvent e(width, height);
                EventDispatcher::getInstance()->dispatch(e); 
            });
            glfwSetWindowCloseCallback(nativeWindow, [](GLFWwindow* window)
            {
                WindowCloseEvent e;
                EventDispatcher::getInstance()->dispatch(e);
            });

            // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwSetCursorPosCallback(nativeWindow, [](GLFWwindow* window, double xPos, double yPos)
            {
                MouseMoveEvent e(xPos, yPos);
                EventDispatcher::getInstance()->dispatch(e);
            });
            glfwSetScrollCallback(nativeWindow, [](GLFWwindow* window, double xOffset, double yOffset)
            {
                MouseScrollEvent e((float) yOffset);
                EventDispatcher::getInstance()->dispatch(e);
            });
            
            glfwSetMouseButtonCallback(nativeWindow, [](GLFWwindow* window, int button, int action, int mods)
            {
                switch (action)
                {
                    case GLFW_PRESS:
                    {
                        MousePressEvent e(button);
                        EventDispatcher::getInstance()->dispatch(e);
                        break;
                    }
                    case GLFW_RELEASE:
                    {
                        MouseReleaseEvent e(button);
                        EventDispatcher::getInstance()->dispatch(e);
                        break;
                    }
                }

            });
            glfwSetKeyCallback(nativeWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
            {
                switch (action)
                {
                    case GLFW_PRESS:
                    {
                        KeyPressEvent e(key, 0);
                        EventDispatcher::getInstance()->dispatch(e);
                        break;
                    }
                    case GLFW_RELEASE:
                    {
                        KeyReleaseEvent e(key);
                        EventDispatcher::getInstance()->dispatch(e);
                        break;
                    }
                    case GLFW_REPEAT:
                    {
                        KeyPressEvent e(key, true);
                        EventDispatcher::getInstance()->dispatch(e);
                        break;
                    }
                }
            });
            return;
        }

        ~WindowGLFW() 
        { 
            SF_LOGW("Window Destructor");
            shutdown(); 
        }

        void updateWindow()
        {
            // float currentFrame = glfwGetTime();
            // deltaTime = currentFrame - lastFrame;
            // lastFrame = currentFrame;

            context->SwapBuffers();
            glfwPollEvents();
            // processInput(deltaTime);

            // return deltaTime;
        }

        void shutdown()
        {
            SF_LOGW("Shutting down window");
            glfwDestroyWindow(nativeWindow);

            // TODO add support for multiple windows-----------------------
            glfwTerminate();
            // TODO add support for multiple windows-----------------------
        }
        void *getNativeWindow() { return (void *)nativeWindow; }
        virtual void onEvent(Event &e) override
        {

        }
    };
} // namespace Snowflake
