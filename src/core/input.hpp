#pragma once

#include <unordered_map>

class Input
{
    private:
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
    // TODO: Function which returns 1 if a key has been down
    bool IsKeyDown(int key);
    // Returns 1 if a key was just released
    bool IsKeyReleased(int key);
};