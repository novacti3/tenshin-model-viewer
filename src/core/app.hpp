#pragma once

#include "window.hpp"
#include "../components/camera.hpp"

#include <glm/vec2.hpp>

#include <string>

class App
{
    private:
    Window *_window;
    Camera *_cam;

    public:
    App(){}
    ~App(){}

    public:
    bool Init(const glm::uvec2 windowSize, const std::string windowTitle);
    void LoadResources();
    void PollInput(float deltaTime);
    void Update(float deltaTime);
    void Render();
    void Cleanup();

    inline Window *getWindow() { return _window; }
};