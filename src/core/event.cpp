#include "event.hpp"

// NOTE: Move stuff to their own cpp files?

EventSender::~EventSender()
{
    for(EventListener *listener: _listeners)
    {
        listener = nullptr;
    }
}

void EventSender::AddListener(EventListener *listener)
{
    if(!ContainsListener(listener))
    {
        _listeners.push_back(listener);
    }
}

void EventSender::RemoveListener(EventListener *listener)
{
    if(ContainsListener(listener))
    {
        for (auto i = _listeners.begin(); i < _listeners.end(); i++)
        {
            if(*i == listener)
            {
                _listeners.erase(i);
            }
        }
        
    }
}

bool EventSender::ContainsListener(EventListener *listener)
{
    for(EventListener *entry: _listeners)
    {
        if(entry == listener)
        {
            return true;
        }
    }

    return false;
}

void EventSender::NotifyListeners(Event &event)
{
    for(EventListener *listener: _listeners)
    {
        listener->OnEvent(event);
    }
}