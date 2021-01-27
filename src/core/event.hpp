#pragma once

enum class EventType
{
    EMPTY = 0,
    WINDOW_RESIZED_EVENT
    // LOG_MESSAGE_EVENT
    // TODO: Add more events
};

#include <utility>
class Event
{
    protected:
    EventType _type;

    public:
    Event(): _type(EventType::EMPTY) {}
    Event(EventType type): _type(std::move(type)) {}
    virtual ~Event() = default;
    // NOTE: Remove copy and move constructors and operators?

    public:
    EventType getType() { return _type; }
};

#include <glm/vec2.hpp>
class WindowResizedEvent final : public Event
{
    private:
    glm::vec2 _newSize;

    public:
    WindowResizedEvent() = delete;
    WindowResizedEvent(EventType type, glm::vec2 newSize): Event(type), _newSize(newSize) {}
    ~WindowResizedEvent() = default;
    // NOTE: Remove copy and move constructors and operators?

    public:
    glm::vec2 getSize() { return _newSize; }
};

// #include <string>
// class LogMessageEvent final : public Event
// {
//     private:
//     std::string _message;

//     public:
//     LogMessageEvent(std::string message): _message(std::move(message)) {}
//     ~LogMessageEvent() = default;
//     // NOTE: Remove copy and move constructors and operators?

//     public:
//     const std::string &getMessage() { return _message; }
// }

class EventListener
{
    public:
    virtual void OnEvent(Event &event) = 0;
};

#include <vector>
class EventSender
{
    private:
    std::vector<EventListener*> _listeners;

    protected:
    EventSender() = default;
    virtual ~EventSender()
    {
        for(EventListener *listener: _listeners)
        {
            listener = nullptr;
        }
    }

    public:
    void AddListener(EventListener *listener)
    {
        if(!ContainsListener(listener))
        {
            _listeners.push_back(listener);
        }
    }
    void RemoveListener(EventListener *listener)
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
    // NOTE: Maybe make this return a tuple with an iterator to the listener as well
    bool ContainsListener(EventListener *listener)
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

    protected:
    void NotifyListeners(Event &event)
    {
        for(EventListener *listener: _listeners)
        {
            listener->OnEvent(event);
        }
    }
};