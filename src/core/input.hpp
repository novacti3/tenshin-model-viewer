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
    std::vector<IKeybind*> _keybinds;

    public:
    Action(ActionType type, std::vector<IKeybind*> keybinds): _type(type), _keybinds(std::move(keybinds)) {} 
    virtual ~Action()
    {
        for(IKeybind *keybind: _keybinds)
        {
            delete keybind;
            keybind = 0;
        }
    }

    public:
    ActionType getType() const { return _type; }
    const std::vector<IKeybind*> &getKeybinds() const { return _keybinds; }
};

// TODO: Add support for different keybinds for the same action (eg. move cam with WASD, arrow keys and mouse)
// TODO: Modifier keys (eg. allow CTRL+O)
// TODO: Add mouse input support
class Input
{
    private:
    std::unordered_map<std::string, Action*> _actions;
    using BoundFuncsList = std::vector<std::function<void(Action&)>>;
    std::unordered_map<std::string, BoundFuncsList> _boundFunctions;

    std::unordered_map<int, bool> _currentFrameKeyMap;
    std::unordered_map<int, bool> _prevFrameKeyMap;

    public:
    Input();
    ~Input();

    public:
    // Updates the provided key in THIS FRAME'S keymap
    void UpdateKey (int key, bool state);
    // Stores the current frame's keymap and prepares it for the next frame 
    void StoreKeys();

    const Action* const GetAction(const std::string &name);
    void BindFuncToAction(const std::string &actionName, std::function<void(Action&)> func);
    void UnbindFuncFromAction(const std::string &actionName, std::function<void(Action&)> func);

    private:
    bool IsKeyPressed(int key);
    bool IsKeyDown(int key);
    bool IsKeyReleased(int key);

    void ExecuteActions();
};