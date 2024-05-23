#pragma once
#include "events.h"
#include "event_dispatcher.h"
#include "input.h"
#include "window.h"
namespace Snowflake {
    class Application : public EventConsumer
    {
        static Application* instance;
    protected:
        bool running;
        Window* window;
    public:
        Application()
        {
            if(instance != nullptr)
            {
                SF_LOGE("Application already created");
            }
            instance = this;

            window = new Snowflake::WindowGLFW();
            running = true; 

        }

        virtual void onUpdate() = 0;
        
        void run()
        {
            int i = 1;
            SF_LOGI("RunLoop");

            while (running)
            {

                onUpdate();
                window->updateWindow();
            }
            window->shutdown();
        }

        virtual void shutdown()
        {
            SF_LOGI("Shutting down");
            running = false;
        }
     
        virtual void onEvent(Event &e) override
        {

        }
     
        Window* getApplicationWindow() { return window; }
     
        static inline Application* get() {return instance; }
    };
	Application* Application::instance = nullptr;

    Application* create_application();
}