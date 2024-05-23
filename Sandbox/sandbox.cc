#include <string>
#include <vector>
#include "Snowflake/snowflake.h"

class Sandbox : public Snowflake::Application
{
public:
    Sandbox() 
    {
        Snowflake::EventDispatcher::getInstance()->setCallback(Snowflake::eventType::APPLICATION_RESIZE, this);
        Snowflake::EventDispatcher::getInstance()->setCallback(Snowflake::eventType::APPLICATION_CLOSE, this);
        Snowflake::EventDispatcher::getInstance()->setCallback(Snowflake::eventType::KEYBOARD_PRESS, this);
        Snowflake::EventDispatcher::getInstance()->setCallback(Snowflake::eventType::KEYBOARD_RELEASE, this);
        Snowflake::EventDispatcher::getInstance()->setCallback(Snowflake::eventType::MOUSE_MOVE, this);
        Snowflake::EventDispatcher::getInstance()->setCallback(Snowflake::eventType::MOUSE_PRESS, this);
        Snowflake::EventDispatcher::getInstance()->setCallback(Snowflake::eventType::MOUSE_RELEASE, this);
        Snowflake::EventDispatcher::getInstance()->setCallback(Snowflake::eventType::MOUSE_SCROLL, this);
    }
    ~Sandbox() {}

    virtual void onUpdate() override
    {
        // SF_LOGI("onUpdate!");
        if (Snowflake::Input::isKeyPressed(SF_KEY_TAB))
            SF_LOGI("Tab pressed!");
    }
    
    virtual void onEvent(Snowflake::Event &e) override
    {
        if(e.getType() == Snowflake::APPLICATION_CLOSE)
            shutdown();
        else if(e.getType() == Snowflake::APPLICATION_RESIZE)
        {
            SF_LOGI("Application event recieved %s", e.getName());
        }
        else if(e.getType() == Snowflake::KEYBOARD_PRESS)
        {
            SF_LOGI("event recieved %s", e.getName());
        }
        else if(e.getType() == Snowflake::KEYBOARD_RELEASE)
        {
            SF_LOGI("event recieved %s", e.getName());
        }
        else if(e.getType() == Snowflake::MOUSE_MOVE)
        {
            auto me = (Snowflake::MouseMoveEvent*) &e;
            SF_LOGI("event recieved %s | x = %f, y = %f", e.getName(), me->getX(), me->getY());
        }
        else if(e.getType() == Snowflake::MOUSE_PRESS)
        {
            SF_LOGI("event recieved %s", e.getName());
        }
        else if(e.getType() == Snowflake::MOUSE_RELEASE)
        {
            SF_LOGI("event recieved %s", e.getName());
        }
        else if(e.getType() == Snowflake::MOUSE_SCROLL)
        {
            SF_LOGI("event recieved %s", e.getName());
            auto me = (Snowflake::MouseScrollEvent*) &e;
            SF_LOGI("event recieved %s | offset = %f", e.getName(), me->getOffset());
        }
    }
};

Snowflake::Application *Snowflake::create_application()
{
    return new Sandbox();
}