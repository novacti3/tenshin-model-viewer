#pragma once

#include <glm/vec2.hpp>

#include <vector>
#include <utility>

enum class EventType
{
    EMPTY = 0,
    WINDOW_RESIZED_EVENT
    // LOG_MESSAGE_EVENT
    // TODO: Add more events
};

class Event
{
    protected:
    EventType _type;

    public:
    Event(): _type(EventType::EMPTY) {}
    explicit Event(EventType type): _type(std::move(type)) {}
    virtual ~Event() = default;
    // NOTE: Remove copy and move constructors and operators?

    public:
    EventType getType() { return _type; }
};

class WindowResizedEvent final : public Event
{
    private:
    glm::vec2 _newSize;

    public:
    WindowResizedEvent() = delete;
    explicit WindowResizedEvent(EventType type, glm::vec2 newSize): Event(type), _newSize(newSize) {}
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

class EventSender
{
    private:
    std::vector<EventListener*> _listeners;

    protected:
    EventSender() = default;
    virtual ~EventSender();

    public:
    void AddListener(EventListener *listener);
    void RemoveListener(EventListener *listener);
    // NOTE: Maybe make this return a tuple with an iterator to the listener as well
    bool ContainsListener(EventListener *listener);

    protected:
    void NotifyListeners(Event &event);
};