#pragma once

#include <array>

struct Key
{
    int keyCode;
    int state;

    Key(){}
    Key(int keyCode, int state)
    {
        this->keyCode = keyCode;
        this->state = state;
    }
    ~Key(){}
};

class Input
{
    private:
    std::array<Key, 512> _keys;
    std::array<Key, 512> _prevKeys;

    public:
    Input();
    ~Input() = default;

    public:
    void UpdateKey(Key key);
    // TODO: Find a better name
    void SaveKeys();
    
    // Returns 1 if a key was just pressed
    bool IsKeyPressed(int key);
    // TODO: Function which returns 1 if a key has been down
    // Returns 1 if a key was just released
    bool IsKeyReleased(int key);
};