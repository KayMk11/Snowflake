#pragma once
// #include "core.h"
namespace Snowflake
{
    enum eventType
    {
        MOUSE_MOVE,
        MOUSE_SCROLL,
        MOUSE_PRESS,
        MOUSE_RELEASE,
        KEYBOARD_PRESS,
        KEYBOARD_RELEASE,
        APPLICATION_CLOSE,
        APPLICATION_RESIZE,
        // none
    };

    class Event
    {
    protected:
        eventType type;
        std::string name;

    public:
        Event(eventType type, std::string name) : type(type), name(name) {}
        eventType getType() { return type; }
        const char *getName() { return name.data(); }
    };

    class EventConsumer
    {
    public:
        virtual void onEvent(Event &e) = 0;
    };

    // -------------------------------Application Events--------------------------------------
    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() : Event(eventType::APPLICATION_CLOSE, "WindowCloseEvent") {}
    };

    class WindowResizeEvent : public Event
    {
        int width, height;

    public:
        WindowResizeEvent(int width, int height) : Event(eventType::APPLICATION_RESIZE, "WindowResizeEvent"), width(width), height(height) {}
    };
    // -------------------------------Application Events--------------------------------------

    // -------------------------------Input Events--------------------------------------------

    class KeyPressEvent : public Event
    {
    protected:
        int mKeyCode;
        int mIsRepeat;
    public:
        KeyPressEvent(int keyCode, bool isRepeat = false) : Event(eventType::KEYBOARD_PRESS, "KeyPressEvent"), mKeyCode(keyCode), mIsRepeat(isRepeat) {}
        int getKeyCode() { return mKeyCode; }
        bool isRepeat() { return mIsRepeat; }
    };

    class KeyReleaseEvent : public Event
    {
    protected:
        int mKeyCode;

    public:
        KeyReleaseEvent(int keyCode) : Event(eventType::KEYBOARD_RELEASE, "KeyReleaseEvent"), mKeyCode(keyCode) {}
        int getKeyCode() { return mKeyCode; }
    };

    class MousePressEvent : public Event
    {
    protected:
        int mKeyCode;

    public:
        MousePressEvent(int keyCode) : Event(eventType::MOUSE_PRESS, "MousePressEvent"), mKeyCode(keyCode) {}
        int getKeyCode() { return mKeyCode; }
    };

    class MouseReleaseEvent : public Event
    {
    protected:
        int mKeyCode;

    public:
        MouseReleaseEvent(int keyCode) : Event(eventType::MOUSE_RELEASE, "MouseReleaseEvent"), mKeyCode(keyCode) {}
        int getKeyCode() { return mKeyCode; }
    };

    class MouseMoveEvent : public Event
    {
    protected:
        float mX, mY;

    public:
        MouseMoveEvent(float x, float y) : Event(eventType::MOUSE_MOVE, "MouseMoveEvent"), mX(x), mY(y) {}
        float getX() { return mX; }
        float getY() { return mY; }
    };

    class MouseScrollEvent : public Event
    {
    protected:
        float mOffset;

    public:
        MouseScrollEvent(float offset) : Event(eventType::MOUSE_SCROLL, "MouseScrollEvent"), mOffset(offset) {}
        float getOffset() { return mOffset; }
    };
    // -------------------------------Input Events--------------------------------------------

} // namespace Snowflake
