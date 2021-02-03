#pragma once

#include "core/event.hpp"
#include "core/window.hpp"
#include "core/input.hpp"
#include "components/camera.hpp"

#include <glm/vec2.hpp>

#include <string>
#include <functional>

class App final : public EventListener
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
    void Update(float deltaTime);
    void Render();
    void Cleanup();

    inline Window *getWindow() { return _window; }

    static void GLFWKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) { _onKeyPressed(key, action); }

    private:
    void OnEvent(Event &event) override;
    void OnKeyPressed(int key, int action);

    // TODO: Unstaticify this shit and do the same mumbo-jumbo as with the rest
    static void QuitProgram(Action& action);
};