#pragma once
#include "events.h"

namespace Snowflake
{
    class EventDispatcher
    {
        static EventDispatcher *instance;
        std::vector<EventConsumer *> listeners[20]; //hardcoding number of Events supported
        EventDispatcher(){};


    public:
        EventDispatcher(EventDispatcher &other) = delete;
        void operator=(const EventDispatcher &) = delete;



        static EventDispatcher *getInstance()
        {
            if(instance == NULL)
                instance = new EventDispatcher();
            return instance;
        }
        void setCallback(int type, EventConsumer *consumer) 
        {
            listeners[type].emplace_back(consumer);
        }
        void dispatch(Event &e)
        {
            int type = e.getType();
            for (auto consumer : listeners[type])
            {
                consumer->onEvent(e);
            }
        }
    };
    EventDispatcher* EventDispatcher::instance = NULL;
} // namespace Snowflake
