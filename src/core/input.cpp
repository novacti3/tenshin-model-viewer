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

    // TODO: Eventually load all of these actions from some sort of keybinds file that's also editable by the user
    _actions.insert(std::make_pair("QuitProgram", Action(ActionType::Button, {ButtonKeybind(GLFW_KEY_ESCAPE)} )));
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

const Action* const Input::GetAction(const std::string &name)
{
    Action *action = &_actions.at(name); 
    return action != nullptr ? action : nullptr;
}

void Input::BindFuncToAction(const std::string &actionName, std::function<void(Action&)> func)
{
    // Check if the given Action even exists in the actions map
    if(GetAction(actionName) == nullptr)
    {
        // NOTE: some sort of assert here?
        return;
    }

    // Check if the given Action already has an entry in boundFuncs map. If not, add it
    if(_boundFunctions.find(actionName) == _boundFunctions.end())
    {
        _boundFunctions.insert(std::make_pair(actionName, BoundFuncsList{func}));
    }
    else
    {
        BoundFuncsList boundFuncs = _boundFunctions.at(actionName);

        // Add the function to the bound funcs under the provided Action if the same func isn't already bound to it
        // (prevents calling the func several times)
        for(auto boundFunc: boundFuncs)
        {
            if(boundFunc.target_type() == func.target_type())
            {
                return;
            }
        }

        boundFuncs.push_back(func);
    }
}

void Input::UnbindFuncFromAction(const std::string &actionName, std::function<void(Action&)> func)
{
    // Check if the given Action even exists in the actions map
    if(GetAction(actionName) == nullptr)
    {
        // NOTE: some sort of assert here?
        return;
    }

    // Check if there even are any funcs bound to provided Action
    if(_boundFunctions.find(actionName) == _boundFunctions.end())
    {
        return;
    }
    else
    {
        BoundFuncsList boundFuncs = _boundFunctions.at(actionName);

        // Remove the funct from the Action if it's in the list
        for(auto i = boundFuncs.begin(); i < boundFuncs.end(); i++)
        {
            if((*i).target_type() == func.target_type())
            {
                boundFuncs.erase(i);
                return;
            }
        }
    }
}