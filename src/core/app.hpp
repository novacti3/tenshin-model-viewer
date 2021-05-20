#pragma once

#include "core/singleton.hpp"
#include "core/event.hpp"
#include "core/window.hpp"
#include "core/input.hpp"
#include "core/scene.hpp"

#include <glm/vec2.hpp>

#include <string>
#include <functional>

// TODO: Turn into singleton
class App final : public Singleton<App>, public EventListener
{
    friend class Singleton<App>;

    private:
    std::vector<Scene*> _scenes;
    Scene* _currentScene;

    static std::function<void(int, int)> _onKeyPressed;
    static TwoDimensionalActionFunc _onRotateCam;

    const float ROT_SPEED = 1.0f;
    const float MIN_PITCH = -90.0f;
    const float MAX_PITCH = 90.0f;
    // static float elevationSpeed = 0.05f;
    const float ZOOM_SPEED = 0.05f;
    // float zoomAmount = 0.0f;
    const float MIN_ZOOM = 0.5f;
    const float MAX_ZOOM = 5.0f;

    private:
    App() = default;
    ~App() = default;

    public:
    bool Init(const glm::uvec2 windowSize, const std::string windowTitle);
    void LoadResources();
    void Update(float deltaTime);
    void Render();
    void Cleanup();

    private:
    void OnEvent(Event &event) override;
    void OnKeyPressed(int key, int action);
    void OnRotateCam(Action &action, glm::ivec2 value);

    static void GLFWKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) { _onKeyPressed(key, action); }
    // NOTE: Maybe take in a const Action ref so it can't be changed
    static void QuitProgram(Action& action);
    static void RotateCamera(Action &action, glm::ivec2 value) { _onRotateCam(action, value); }
};