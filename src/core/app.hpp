#pragma once

#include "core/event.hpp"
#include "core/window.hpp"
#include "core/input.hpp"
#include "core/scene.hpp"

#include <glm/vec2.hpp>

#include <string>
#include <functional>

// TODO: Turn into a static class
class App final : public EventListener
{
    private:
    std::vector<Scene*> _scenes;
    Scene* _currentScene;

    static std::function<void(int, int)> _onKeyPressed;
    static std::function<void(Action&, glm::ivec2 value)> _rotateCam;

    TransformComponent _cubeTransform;

    const float ROT_SPEED = 1.0f;
    // float _yaw = 0.0f;
    // float _pitch = 0.0f;
    const float MIN_PITCH = -90.0f;
    const float MAX_PITCH = 90.0f;
    // static float elevationSpeed = 0.05f;
    const float ZOOM_SPEED = 0.05f;
    // float zoomAmount = 0.0f;
    const float MIN_ZOOM = 0.5f;
    const float MAX_ZOOM = 5.0f;

    public:
    App(){}
    ~App(){}

    public:
    bool Init(const glm::uvec2 windowSize, const std::string windowTitle);
    void LoadResources();
    void Update(float deltaTime);
    void Render();
    void Cleanup();

    // inline Window *getWindow() { return _window; }

    static void GLFWKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) { _onKeyPressed(key, action); }

    private:
    void OnEvent(Event &event) override;
    void OnKeyPressed(int key, int action);
    void RotateCam(Action &action, glm::ivec2 value);

    // TODO: Unstaticify this shit and do the same mumbo-jumbo as with the rest
    // NOTE: Maybe take in a const Action ref so it can't be changed
    static void QuitProgram(Action& action);
    static void RotateCamera(Action &action, glm::ivec2 value) { _rotateCam(action, value); }
};