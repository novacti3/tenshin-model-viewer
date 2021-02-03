#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <functional>

class IKeybind
{
    public:
    IKeybind() = default;
    virtual ~IKeybind() = default;
};

class ButtonKeybind : public IKeybind
{
    private:
    int _keyCode;

    public:
    ButtonKeybind(int keyCode): _keyCode(keyCode) {}
    virtual ~ButtonKeybind() = default;

    public:
    int getKeyCode() { return _keyCode; }
};

enum class ActionType
{
    Button = 0,
    // OneDimensional,
    // TwoDimensional
};

class Action
{
    private:
    ActionType _type;
    std::vector<IKeybind> _keybinds;

    public:
    Action(ActionType type, std::vector<IKeybind> keybinds): _type(type), _keybinds(std::move(_keybinds)) {} 
    virtual ~Action() = default;

    public:
    ActionType getType() const { return _type; }
    const std::vector<IKeybind> &getKeybinds() const { return _keybinds; }
};

// TODO: Add support for different keybinds for the same action (eg. move cam with WASD, arrow keys and mouse)
// TODO: Modifier keys (eg. allow CTRL+O)
// TODO: Add mouse input support
class Input
{
    private:
    std::unordered_map<std::string, Action> _actions;

    using BoundFuncsList = std::vector<std::function<void(Action&)>>;
    std::unordered_map<std::string, BoundFuncsList> _boundFunctions;

    std::unordered_map<int, bool> _keyMap;
    std::unordered_map<int, bool> _prevKeyMap;

    public:
    Input();
    ~Input() = default;

    public:
    void UpdateKey (int key, bool state);
    // TODO: Find a better name
    void SaveKeys();
    
    // Returns 1 if a key was just pressed
    bool IsKeyPressed(int key);
    // Returns 1 if a key has been down
    bool IsKeyDown(int key);
    // Returns 1 if a key was just released
    bool IsKeyReleased(int key);

    // TODO: Function which sends an OnActionStarted event (or something like that) along with the Action which happened
    const Action* const GetAction(const std::string &name);
    void BindFuncToAction(const std::string &actionName, std::function<void(Action&)> func);
    void UnbindFuncFromAction(const std::string &actionName, std::function<void(Action&)> func);
};