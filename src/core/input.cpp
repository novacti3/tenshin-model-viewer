#include "input.hpp"

#include <GLFW/glfw3.h>

Input::Input()
{
    for(Key key: _keys)
    {
        key.state = GLFW_RELEASE;
    }

    for(Key prevKey: _prevKeys)
    {
        prevKey.state = GLFW_RELEASE;
    } 
}

void Input::UpdateKey(Key key)
{
    if(key.keyCode < _keys.size())
    {
        _keys[key.keyCode] = std::move(key);
    }
}

void Input::SaveKeys()
{
    _prevKeys = _keys;

    for(Key key: _keys)
    {
        key.state = 0;
    }
}

// Function which returns 1 if a key was just pressed
bool Input::IsKeyPressed(int key)
{
    return _prevKeys[key].state != GLFW_RELEASE && _keys[key].state == GLFW_PRESS;
}
// Function which returns 1 if a key was just released
bool Input::IsKeyReleased(int key)
{
    return _prevKeys[key].state != GLFW_RELEASE && _keys[key].state == GLFW_RELEASE;
}