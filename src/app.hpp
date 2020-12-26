#pragma once

#include "window.hpp"

class App
{
    private:
    Window *_window;

    public:
    App(){}
    ~App(){}

    public:
    void Init(Window *window);
    void PollInput(float deltaTime);
    void Update(float deltaTime);
    void Render();
    void Cleanup();
};