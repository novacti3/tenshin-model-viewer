#include "input.hpp"

#include "core/log.hpp"

#include <GLFW/glfw3.h>

void Input::Init()
{
    for (size_t i = 0; i < 512; i++)
    {
        _currentFrameKeyMap[i] = false;
    }
    
    for (size_t i = 0; i < 512; i++)
    {
        _prevFrameKeyMap[i] = false;
    }

    // TODO: Eventually load all of these actions from some sort of keybinds file that's also editable by the user
    _actions.insert(std::make_pair("QuitProgram", new Action(ActionType::Button, { new ButtonKeybind(GLFW_KEY_ESCAPE) })));
    _actions.insert(std::make_pair("RotateCamera", new Action(ActionType::TwoDimensional, 
    { 
        new TwoDimensionalKeybind(GLFW_KEY_D, GLFW_KEY_A, GLFW_KEY_W, GLFW_KEY_S),
        new TwoDimensionalKeybind(GLFW_KEY_RIGHT, GLFW_KEY_LEFT, GLFW_KEY_UP, GLFW_KEY_DOWN)
    })));
}

void Input::Cleanup()
{
    for(auto entry: _actions)
    {
        delete entry.second;
        entry.second = nullptr;
    }

    Log::LogInfo("Input destroyed");
}

void Input::UpdateKey (int key, bool state)
{
    if(key < _currentFrameKeyMap.size())
    {
        _currentFrameKeyMap[key] = state;
        ExecuteActions();
    }
}

void Input::StoreKeys()
{
    _prevFrameKeyMap = _currentFrameKeyMap;
}

const Action* const Input::GetAction(const std::string &name)
{
    Action *action = _actions.at(name); 
    return action != nullptr ? action : nullptr;
}

// Button action 
void Input::BindFuncToAction(const std::string &actionName, ButtonActionFunc func)
{
    // Check if the given Action even exists in the actions map
    if(GetAction(actionName) == nullptr)
    {
        // NOTE: some sort of assert here?
        return;
    }

    using BoundFuncsList = std::vector<ButtonActionFunc>;

    // Check if the given Action already has an entry in the appropriate map. If not, add it
    if(_buttonActionFunctions.find(actionName) == _buttonActionFunctions.end())
    {
        _buttonActionFunctions.insert(std::make_pair(actionName, BoundFuncsList{func}));
    }
    else
    {
        BoundFuncsList boundFuncs = _buttonActionFunctions.at(actionName);

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
void Input::UnbindFuncFromAction(const std::string &actionName, ButtonActionFunc func)
{
    // Check if the given Action even exists in the actions map
    if(GetAction(actionName) == nullptr)
    {
        // NOTE: some sort of assert here?
        return;
    }

    using BoundFuncsList = std::vector<ButtonActionFunc>;

    // Check if there even are any funcs bound to provided Action
    if(_buttonActionFunctions.find(actionName) == _buttonActionFunctions.end())
    {
        return;
    }
    else
    {
        BoundFuncsList boundFuncs = _buttonActionFunctions.at(actionName);

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

// One Dimensional action 
void Input::BindFuncToAction(const std::string &actionName, OneDimensionalActionFunc func)
{
    // Check if the given Action even exists in the actions map
    if(GetAction(actionName) == nullptr)
    {
        // NOTE: some sort of assert here?
        return;
    }

    using BoundFuncsList = std::vector<OneDimensionalActionFunc>;

    // Check if the given Action already has an entry in the appropriate map. If not, add it
    if(_oneDimensionalActionFunctions.find(actionName) == _oneDimensionalActionFunctions.end())
    {
        _oneDimensionalActionFunctions.insert(std::make_pair(actionName, BoundFuncsList{func}));
    }
    else
    {
        BoundFuncsList boundFuncs = _oneDimensionalActionFunctions.at(actionName);

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
void Input::UnbindFuncFromAction(const std::string &actionName, OneDimensionalActionFunc func)
{
    // Check if the given Action even exists in the actions map
    if(GetAction(actionName) == nullptr)
    {
        // NOTE: some sort of assert here?
        return;
    }

    using BoundFuncsList = std::vector<OneDimensionalActionFunc>;

    // Check if there even are any funcs bound to provided Action
    if(_oneDimensionalActionFunctions.find(actionName) == _oneDimensionalActionFunctions.end())
    {
        return;
    }
    else
    {
        BoundFuncsList boundFuncs = _oneDimensionalActionFunctions.at(actionName);

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

// Two Dimensional action 
void Input::BindFuncToAction(const std::string &actionName, TwoDimensionalActionFunc func)
{
    // Check if the given Action even exists in the actions map
    if(GetAction(actionName) == nullptr)
    {
        // NOTE: some sort of assert here?
        return;
    }

    using BoundFuncsList = std::vector<TwoDimensionalActionFunc>;

    // Check if the given Action already has an entry in the appropriate map. If not, add it
    if(_twoDimensionalActionFunctions.find(actionName) == _twoDimensionalActionFunctions.end())
    {
        _twoDimensionalActionFunctions.insert(std::make_pair(actionName, BoundFuncsList{func}));
    }
    else
    {
        BoundFuncsList boundFuncs = _twoDimensionalActionFunctions.at(actionName);

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
void Input::UnbindFuncFromAction(const std::string &actionName, TwoDimensionalActionFunc func)
{
    // Check if the given Action even exists in the actions map
    if(GetAction(actionName) == nullptr)
    {
        // NOTE: some sort of assert here?
        return;
    }

    using BoundFuncsList = std::vector<TwoDimensionalActionFunc>;

    // Check if there even are any funcs bound to provided Action
    if(_twoDimensionalActionFunctions.find(actionName) == _twoDimensionalActionFunctions.end())
    {
        return;
    }
    else
    {
        BoundFuncsList boundFuncs = _twoDimensionalActionFunctions.at(actionName);

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

bool Input::IsKeyPressed(int key)
{
    return _prevFrameKeyMap[key] == false && _currentFrameKeyMap[key] == true;
}
bool Input::IsKeyDown(int key)
{
    return _currentFrameKeyMap[key];
}
bool Input::IsKeyReleased(int key)
{
    return _prevFrameKeyMap[key] == true && _currentFrameKeyMap[key] == false;
}

void Input::ExecuteActions()
{
    for(auto entry: _actions)
    {
        const std::string &actionName = entry.first;
        Action &action = *(entry.second);

        // Each ActionType requires slightly different triggering logic. Use the appropriate one based on the type of the current Action
        switch(action.getType())
        {
            case ActionType::Button:
            {
                // Loop through each keybind and check if the key isn't pressed. 
                // If it is, call all of the functions bound to the Action in question
                // NOTE: Not exiting out of the loop once the first suitable key is pressed might theoretically result in the Action triggering twice
                for (auto i = action.getKeybinds().begin(); i < action.getKeybinds().end(); i++)
                {
                    // NOTE: dynamic_cast is used here to cast down from parent class IKeybind to a child class. 
                    // const_cast is used to de-constify the const IKeybind* returned by Action.getKeybinds()
                    // The cast object MUST be a pointer, otherwise object slicing and a read-access violation occurs (more info about object slicing in the Action class declaration)  
                    ButtonKeybind *keybind = dynamic_cast<ButtonKeybind*>(const_cast<IKeybind*>(*i));
                    if(IsKeyPressed(keybind->getKeyCode()))
                    {
                        for(auto boundFunc: _buttonActionFunctions[actionName])
                        {
                            boundFunc(action);
                        }
                    }
                }
            }
            break;

            case ActionType::OneDimensional:
            {
                // Loop through each "keybind set" and check if any of the keys aren't currently down. 
                // If the positive key is down return 1, if the negative key is down return -1 in all of the functions bound to the current Action 
                for (auto i = action.getKeybinds().begin(); i < action.getKeybinds().end(); i++)
                {
                    OneDimensionalKeybind *keybind = dynamic_cast<OneDimensionalKeybind*>(const_cast<IKeybind*>(*i));
                    if(IsKeyDown(keybind->getPositiveKeyCode()))
                    {
                        for(auto boundFunc: _oneDimensionalActionFunctions[actionName])
                        {
                            boundFunc(action, 1);
                        }
                    }
                    else if(IsKeyDown(keybind->getNegativeKeyCode()))
                    {
                        for(auto boundFunc: _oneDimensionalActionFunctions[actionName])
                        {
                            boundFunc(action, -1);
                        }
                    }
                } 
            }
            break;

            // Loop through each "keybind set" and check if any of the keys for each axis aren't currently down.
            // Construct an ivec2 based on the combination of positive and negative keys held down and return it in all of the functions bound to this Action
            case ActionType::TwoDimensional:
            {
                for (auto i = action.getKeybinds().begin(); i < action.getKeybinds().end(); i++)
                {
                    TwoDimensionalKeybind *keybind = dynamic_cast<TwoDimensionalKeybind*>(const_cast<IKeybind*>(*i));
                    
                    // NOTE: The way this is set up now doesn't allow for two "keybind sets" to influence each other
                    // (eg. you can't press W and right arrow at the same time and get (1, 1))
                    // This could probably be changed by moving the value var outside of the keybinds loop if necesarry
                    glm::ivec2 value;
                    // X axis
                    if(IsKeyDown(keybind->getPositiveXKeyCode()))
                    {
                        value.x = 1;
                    }
                    else if(IsKeyDown(keybind->getNegativeXKeyCode()))
                    {
                        value.x = -1;
                    }
                    else
                    {
                        value.x = 0;
                    }

                    // Y axis
                    if(IsKeyDown(keybind->getPositiveYKeyCode()))
                    {
                        value.y = 1;
                    }
                    else if(IsKeyDown(keybind->getNegativeYKeyCode()))
                    {
                        value.y = -1;
                    }
                    else
                    {
                        value.y = 0;
                    }

                    if(value.x != 0 || value.y != 0)
                    {
                        for(auto boundFunc: _twoDimensionalActionFunctions[actionName])
                        {
                            boundFunc(action, value);
                        }
                    }
                } 
            }
            break;
        }
    }
}
