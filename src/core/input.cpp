#include "input.hpp"

#include <GLFW/glfw3.h>

Input::Input()
{
    for (size_t i = 0; i < 512; i++)
    {
        _keyMap[i] = false;
    }
    
    for (size_t i = 0; i < 512; i++)
    {
        _prevKeyMap[i] = false;
    }
}

void Input::UpdateKey (int key, bool state)
{
    if(key < _keyMap.size())
    {
        _keyMap[key] = state;
    }
}

void Input::SaveKeys()
{
    _prevKeyMap = _keyMap;
}

// Function which returns 1 if a key was just pressed
bool Input::IsKeyPressed(int key)
{
    // return _prevKeys[key].state != GLFW_RELEASE && _keys[key].state == GLFW_PRESS;
    return _prevKeyMap[key] == false && _keyMap[key] == true;
}
bool Input::IsKeyDown(int key)
{
    return _keyMap[key];
}
// Function which returns 1 if a key was just released
bool Input::IsKeyReleased(int key)
{
    // return _prevKeys[key].state != GLFW_RELEASE && _keys[key].state == GLFW_RELEASE;
    return _prevKeyMap[key] == true && _keyMap[key] == false;
}