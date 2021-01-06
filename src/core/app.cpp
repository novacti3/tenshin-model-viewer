#include "app.hpp"

#include "log.hpp"
#include "resource_manager.hpp"

#include "../rendering/primitives/quad.hpp"
#include "../rendering/primitives/cube.hpp"

#include "../components/transform.hpp"
#include "../components/primitive_renderer.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

std::array<Key, 512> App::_keys;
std::array<Key, 512> App::_prevKeys;

bool App::Init(const glm::uvec2 windowSize, const std::string windowTitle)
{
    // Create window
    _window = new Window();
    if(!_window->Init(windowSize, windowTitle))
    {
        Log::LogFatal("Failed initializing window");
        return false;
    }
    Log::LogInfo("Window initialized");

    glfwSetKeyCallback(_window->getHandle(), App::KeyCallback);

    _cam = new Camera(Transform(glm::vec3(0.0f, 0.0f, 3.0f)), 60.0f, (float)_window->getSize().x/(float)_window->getSize().y, 0.01f, 100.0f);

    return true;
}

void App::LoadResources()
{
    ResourceManager::AddShader(ResourceManager::CreateShaderFromFiles("../../res/shaders/unlit-color.vs", "../../res/shaders/unlit-color.fs"), "unlit-color");
}

void App::Update(float deltaTime)
{
    // TODO: Arcball cam
}

void App::Render()
{
    Cube cube;
    PrimitiveRenderer cubeRenderer(&cube, ResourceManager::GetShader("unlit-color"));

    GL_CALL(glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CALL(glad_glClearColor(0.2f, 0.0f, 0.2f, 1.0f));

    cubeRenderer.Draw(_cubeTransform, _cam->getViewMatrix(), _cam->getProjMatrix());

    glfwSwapBuffers(_window->getHandle());
}

void App::Cleanup()
{
    ResourceManager::Cleanup();

    _window->Cleanup();
    delete _window;
    _window = 0;

    Log::LogInfo("App instance destroyed");
}

void App::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if(key < _keys.size())
    {
        Key newKey(key, action);
        _keys[key] = newKey;
    }
}

void App::UpdateKeys()
{
    _prevKeys = _keys;
}

bool App::IsKeyPressed(int key)
{
    return _keys[key].state == GLFW_PRESS;
}
bool App::IsKeyDown(int key)
{
    return _prevKeys[key].state == GLFW_PRESS && _keys[key].state == GLFW_PRESS;
}
bool App::IsKeyReleased(int key)
{
    return _keys[key].state == GLFW_RELEASE;
}