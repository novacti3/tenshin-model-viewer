#pragma once

#include "core/singleton.hpp"

#include <glm/vec2.hpp>

#include <unordered_map>
#include <vector>
#include <string>
#include <functional>

// The abstract base class for all keybind types. Used in the Action class to "generify" it
class IKeybind
{
    public:
    IKeybind() = default;
    virtual ~IKeybind() = default;
};

// Simple press-a-button true/false keybind
class ButtonKeybind final : public IKeybind
{
    private:
    int _keyCode;

    public:
    ButtonKeybind(int keyCode): _keyCode(keyCode) {}
    ~ButtonKeybind() = default;
    // Copy
    ButtonKeybind(const ButtonKeybind& other): _keyCode(other._keyCode) {}
    ButtonKeybind& operator=(ButtonKeybind other)
    {
        this->_keyCode = other._keyCode;
        return *this;
    }
    // Move
    ButtonKeybind(ButtonKeybind&& other): _keyCode(std::move(other._keyCode)) {}
    ButtonKeybind& operator=(ButtonKeybind&& other)
    {
        this->_keyCode = std::move(other._keyCode);
        return *this;
    }

    public:
    int getKeyCode() const { return _keyCode; }
};

// Keybind with a keycode for 1 and a keycode for -1
class OneDimensionalKeybind final : public IKeybind
{
    private:
    // NOTE: Changing this to a ivec2 would maybe be cleaner
    int _positiveKeyCode, _negativeKeyCode;

    public:
    OneDimensionalKeybind(int positiveKeyCode, int negativeKeyCode): _positiveKeyCode(positiveKeyCode), _negativeKeyCode(negativeKeyCode) {}
    ~OneDimensionalKeybind() = default;
    // Copy
    OneDimensionalKeybind(const OneDimensionalKeybind& other): _positiveKeyCode(other._positiveKeyCode), _negativeKeyCode(other._negativeKeyCode) {}
    OneDimensionalKeybind& operator=(OneDimensionalKeybind other)
    {
        this->_positiveKeyCode = other._positiveKeyCode;
        this->_negativeKeyCode = other._negativeKeyCode;

        return *this;
    }
    // Move
    OneDimensionalKeybind(OneDimensionalKeybind&& other): _positiveKeyCode(std::move(other._positiveKeyCode)), _negativeKeyCode(std::move(other._negativeKeyCode)) {}
    OneDimensionalKeybind& operator=(OneDimensionalKeybind&& other)
    {
        this->_positiveKeyCode = std::move(other._positiveKeyCode);
        this->_negativeKeyCode = std::move(other._negativeKeyCode);

        return *this;
    }

    public:
    int getPositiveKeyCode() const { return _positiveKeyCode; }
    int getNegativeKeyCode() const { return _negativeKeyCode; }
};

// Keybind with two axis, each with a keycode for 1 and -1 respectively
class TwoDimensionalKeybind final : public IKeybind
{
    private:
    // NOTE: Changing this to ivec2s would maybe be cleaner
    int _positiveXKeyCode, _negativeXKeyCode;
    int _positiveYKeyCode, _negativeYKeyCode;

    public:
    TwoDimensionalKeybind(int positiveXKeyCode, int negativeXKeyCode, int positiveYKeyCode, int negativeYKeyCode): _positiveXKeyCode(positiveXKeyCode), _negativeXKeyCode(negativeXKeyCode), _positiveYKeyCode(positiveYKeyCode), _negativeYKeyCode(negativeYKeyCode) {}
    ~TwoDimensionalKeybind() = default;
    // Copy
    TwoDimensionalKeybind(const TwoDimensionalKeybind& other): _positiveXKeyCode(other._positiveXKeyCode), _negativeXKeyCode(other._negativeXKeyCode), _positiveYKeyCode(other._positiveYKeyCode), _negativeYKeyCode(other._negativeYKeyCode) {}
    TwoDimensionalKeybind& operator=(TwoDimensionalKeybind other)
    {
        this->_positiveXKeyCode = other._positiveXKeyCode;
        this->_negativeXKeyCode = other._negativeXKeyCode;
        this->_positiveYKeyCode = other._positiveYKeyCode;
        this->_negativeYKeyCode = other._negativeYKeyCode;

        return *this;
    }
    // Move
    TwoDimensionalKeybind(TwoDimensionalKeybind&& other): _positiveXKeyCode(std::move(other._positiveXKeyCode)), _negativeXKeyCode(std::move(other._negativeXKeyCode)), _positiveYKeyCode(std::move(other._positiveYKeyCode)), _negativeYKeyCode(std::move(other._negativeYKeyCode)) {}
    TwoDimensionalKeybind& operator=(TwoDimensionalKeybind&& other)
    {
        this->_positiveXKeyCode = std::move(other._positiveXKeyCode);
        this->_negativeXKeyCode = std::move(other._negativeXKeyCode);
        this->_positiveYKeyCode = std::move(other._positiveYKeyCode);
        this->_negativeYKeyCode = std::move(other._negativeYKeyCode);

        return *this;
    }

    public:
    int getPositiveXKeyCode() const { return _positiveXKeyCode; }
    int getNegativeXKeyCode() const { return _negativeXKeyCode; }
    int getPositiveYKeyCode() const { return _positiveYKeyCode; }
    int getNegativeYKeyCode() const { return _negativeYKeyCode; }
};

// All of the possible Action types
enum class ActionType
{
    Button = 0,
    OneDimensional,
    TwoDimensional
};

class Action final
{
    private:
    // NOTE: Maybe add a field for the action name?
    ActionType _type;
    // List of all possible keybinds that will trigger this action (the actual triggering depends on the keybind type)
    // A pointer to IKeybind is stored here because casting down to derivatives of the class on a non-pointer causes object slicing
    // (the additional data from the deriving class gets erased)
    std::vector<IKeybind*> _keybinds;

    public:
    Action(ActionType type, std::vector<IKeybind*> keybinds): _type(type), _keybinds(keybinds) {} 
    virtual ~Action()
    {
        for(IKeybind *keybind: _keybinds)
        {
            delete keybind;
            keybind = 0;
        }
    }
    // Copy
    Action(const Action& other): _type(other._type), _keybinds(other._keybinds) {}
    Action& operator=(Action other)
    {
        this->_type = other._type;
        this->_keybinds = other._keybinds;

        return *this;
    }
    // Move
    Action(Action&& other): _type(std::move(other._type)), _keybinds(std::move(other._keybinds)) {}
    Action& operator=(Action&& other)
    {
        this->_type = std::move(other._type);
        this->_keybinds = std::move(other._keybinds);

        return *this;
    }

    public:
    ActionType getType() const { return _type; }
    const std::vector<IKeybind*> &getKeybinds() const { return _keybinds; }
};

// Ease of use type aliases for the function pointers belonging to each ActionType
using ButtonActionFunc = std::function<void(Action&)>;
using OneDimensionalActionFunc = std::function<void(Action&, char value)>;
using TwoDimensionalActionFunc = std::function<void(Action&, glm::ivec2 value)>;

// TODO: Modifier keys (eg. allow CTRL+O)
// TODO: Add mouse input support
class Input final : public Singleton<Input>
{
    friend class Singleton<Input>;

    private:
    // Hashmap of all registered Actions that the input system will check for
    std::unordered_map<std::string, Action*> _actions;

    // Hashmaps of lists of functions bound to Actions inside of _actions
    std::unordered_map<std::string, std::vector<ButtonActionFunc>> _buttonActionFunctions;
    std::unordered_map<std::string, std::vector<OneDimensionalActionFunc>> _oneDimensionalActionFunctions;
    std::unordered_map<std::string, std::vector<TwoDimensionalActionFunc>> _twoDimensionalActionFunctions;

    // Keymaps used to determine the current state of a key
    std::unordered_map<int, bool> _currentFrameKeyMap;
    std::unordered_map<int, bool> _prevFrameKeyMap;

    private:
    Input() = default;
    ~Input() = default;
    public:
    // Copy
    Input(const Input& other) = delete;
    Input& operator=(Input other) = delete;
    // Move
    Input(Input&& other) = delete;
    Input& operator=(Input&& other) = delete;

    public:
    void Init();
    void Cleanup();

    // Updates the provided key in THIS FRAME'S keymap
    void UpdateKey (int key, bool state);
    // Stores the current frame's keymap and prepares it for the next frame 
    void StoreKeys();

    const Action* const GetAction(const std::string &name);
    // Button action
    void BindFuncToAction(const std::string &actionName, ButtonActionFunc func);
    void UnbindFuncFromAction(const std::string &actionName, ButtonActionFunc func);
    // One Dimensional action
    void BindFuncToAction(const std::string &actionName, OneDimensionalActionFunc func);
    void UnbindFuncFromAction(const std::string &actionName, OneDimensionalActionFunc func);
    // Two Dimensional action
    void BindFuncToAction(const std::string &actionName, TwoDimensionalActionFunc func);
    void UnbindFuncFromAction(const std::string &actionName, TwoDimensionalActionFunc func);

    private:
    bool IsKeyPressed(int key);
    bool IsKeyDown(int key);
    bool IsKeyReleased(int key);

    void ExecuteActions();
};