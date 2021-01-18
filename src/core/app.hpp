#pragma once

#include "window.hpp"
#include "input.hpp"
#include "components/camera.hpp"

#include <glm/vec2.hpp>

#include <string>
#include <functional>

class App
{
    private:
    Window *_window;
    Input *_input;
    Camera *_cam;

    static std::function<void(int, int)> _onKeyPressed;

    Transform _cubeTransform;

    public:
    App(){}
    ~App(){}

    public:
    bool Init(const glm::uvec2 windowSize, const std::string windowTitle);
    void LoadResources();
    void ProcessEvents();
    void Update(float deltaTime);
    void Render();
    void Cleanup();

    inline Window *getWindow() { return _window; }

    static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) { _onKeyPressed(key, action); }

    private:
    void OnKeyPressed(int key, int action);
};