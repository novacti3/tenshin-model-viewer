#pragma once

#include <glm/vec2.hpp>
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

class ButtonKeybind final : public IKeybind
{
    private:
    int _keyCode;

    public:
    ButtonKeybind(int keyCode): _keyCode(keyCode) {}
    ~ButtonKeybind() = default;

    public:
    int getKeyCode() const { return _keyCode; }
};

class OneDimensionalKeybind final : public IKeybind
{
    private:
    // NOTE: Changing this to a vec2 would maybe be cleaner
    int _positiveKeyCode, _negativeKeyCode;

    public:
    OneDimensionalKeybind(int positiveKeyCode, int negativeKeyCode): _positiveKeyCode(positiveKeyCode), _negativeKeyCode(negativeKeyCode) {}
    ~OneDimensionalKeybind() = default;

    public:
    int getPositiveKeyCode() const { return _positiveKeyCode; }
    int getNegativeKeyCode() const { return _negativeKeyCode; }
};

class TwoDimensionalKeybind final : public IKeybind
{
    private:
    // NOTE: Changing this to vec2s would maybe be cleaner
    int _positiveXKeyCode, _negativeXKeyCode;
    int _positiveYKeyCode, _negativeYKeyCode;

    public:
    TwoDimensionalKeybind(int positiveXKeyCode, int negativeXKeyCode, int positiveYKeyCode, int negativeYKeyCode): _positiveXKeyCode(positiveXKeyCode), _negativeXKeyCode(negativeXKeyCode), _positiveYKeyCode(positiveYKeyCode), _negativeYKeyCode(negativeYKeyCode) {}
    ~TwoDimensionalKeybind() = default;

    public:
    int getPositiveXKeyCode() const { return _positiveXKeyCode; }
    int getNegativeXKeyCode() const { return _negativeXKeyCode; }
    int getPositiveYKeyCode() const { return _positiveYKeyCode; }
    int getNegativeYKeyCode() const { return _negativeYKeyCode; }
};

enum class ActionType
{
    Button = 0,
    OneDimensional,
    TwoDimensional
};

class Action final
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
    // TODO: Make an alias for all of the function pointers
    std::unordered_map<std::string, std::vector<std::function<void(Action&)>>> _buttonActionFunctions;
    std::unordered_map<std::string, std::vector<std::function<void(Action&, char value)>>> _oneDimensionalActionFunctions;
    std::unordered_map<std::string, std::vector<std::function<void(Action&, glm::ivec2 value)>>> _twoDimensionalActionFunctions;

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
    // Button action
    void BindFuncToAction(const std::string &actionName, std::function<void(Action&)> func);
    void UnbindFuncFromAction(const std::string &actionName, std::function<void(Action&)> func);
    // One Dimensional action
    void BindFuncToAction(const std::string &actionName, std::function<void(Action&, char value)> func);
    void UnbindFuncFromAction(const std::string &actionName, std::function<void(Action&, char value)> func);
    // Two Dimensional action
    void BindFuncToAction(const std::string &actionName, std::function<void(Action&, glm::ivec2 value)> func);
    void UnbindFuncFromAction(const std::string &actionName, std::function<void(Action&, glm::ivec2 value)> func);

    private:
    bool IsKeyPressed(int key);
    bool IsKeyDown(int key);
    bool IsKeyReleased(int key);

    void ExecuteActions();
};