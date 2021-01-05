#pragma once

#include "window.hpp"
#include "../components/camera.hpp"

#include <glm/vec2.hpp>

#include <string>

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

class App
{
    private:
    Window *_window;
    Camera *_cam;
    float _camMovementSpeed = 0.1f;

    Transform _cubeTransform;

    static std::array<Key, 512> _keys;
    static std::array<Key, 512> _prevKeys;

    public:
    App(){}
    ~App(){}

    public:
    bool Init(const glm::uvec2 windowSize, const std::string windowTitle);
    void LoadResources();
    void Update(float deltaTime);
    void Render();
    void Cleanup();

    inline Window *getWindow() { return _window; }

    // FIXME: Unstaticify this shit
    static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    // TODO: Move into Input class or something
    static void UpdateKeys();
    static bool IsKeyPressed(int key);
    static bool IsKeyDown(int key);
    static bool IsKeyReleased(int key);
};