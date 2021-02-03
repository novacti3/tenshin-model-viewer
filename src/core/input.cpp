#include "input.hpp"

#include <GLFW/glfw3.h>

Input::Input()
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
    _actions.insert(std::make_pair("CamYaw", new Action(ActionType::OneDimensional, { new OneDimensionalKeybind(GLFW_KEY_D, GLFW_KEY_A) })));
}

Input::~Input()
{
    for(auto entry: _actions)
    {
        delete entry.second;
        entry.second = nullptr;
    }
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
void Input::BindFuncToAction(const std::string &actionName, std::function<void(Action&)> func)
{
    // Check if the given Action even exists in the actions map
    if(GetAction(actionName) == nullptr)
    {
        // NOTE: some sort of assert here?
        return;
    }

    using BoundFuncsList = std::vector<std::function<void(Action&)>>;

    // Check if the given Action already has an entry in boundFuncs map. If not, add it
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
void Input::UnbindFuncFromAction(const std::string &actionName, std::function<void(Action&)> func)
{
    // Check if the given Action even exists in the actions map
    if(GetAction(actionName) == nullptr)
    {
        // NOTE: some sort of assert here?
        return;
    }

    using BoundFuncsList = std::vector<std::function<void(Action&)>>;

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
void Input::BindFuncToAction(const std::string &actionName, std::function<void(Action&, char value)> func)
{
    // Check if the given Action even exists in the actions map
    if(GetAction(actionName) == nullptr)
    {
        // NOTE: some sort of assert here?
        return;
    }

    using BoundFuncsList = std::vector<std::function<void(Action&, char value)>>;

    // Check if the given Action already has an entry in boundFuncs map. If not, add it
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
void Input::UnbindFuncFromAction(const std::string &actionName, std::function<void(Action&, char value)> func)
{
    // Check if the given Action even exists in the actions map
    if(GetAction(actionName) == nullptr)
    {
        // NOTE: some sort of assert here?
        return;
    }

    using BoundFuncsList = std::vector<std::function<void(Action&, char value)>>;

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

        switch(action.getType())
        {
            case ActionType::Button:
            {
                for (auto i = action.getKeybinds().begin(); i < action.getKeybinds().end(); i++)
                {
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

            // NOTE: Add the rest
        }
    }
}
