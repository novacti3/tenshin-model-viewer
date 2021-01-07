#include "app.hpp"

#include "log.hpp"
#include "resource_manager.hpp"

#include "../rendering/primitives/quad.hpp"
#include "../rendering/primitives/cube.hpp"

#include "../components/transform.hpp"
#include "../components/primitive_renderer.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

std::function<void(int, int)> App::_onKeyPressed;

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

    _input = new Input();
    _cam = new Camera(Transform(glm::vec3(0.0f, 0.0f, 3.0f)), 60.0f, (float)_window->getSize().x/(float)_window->getSize().y, 0.01f, 100.0f);

    _onKeyPressed = [this](int key, int action)
    {
        App::OnKeyPressed(key, action);
    };
    glfwSetKeyCallback(_window->getHandle(), App::KeyCallback);
    
    return true;
}

void App::LoadResources()
{
    ResourceManager::AddShader(ResourceManager::CreateShaderFromFiles("../../res/shaders/unlit-color.vs", "../../res/shaders/unlit-color.fs"), "unlit-color");
}

void App::Update(float deltaTime)
{
    if(_input->IsKeyPressed(GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(_window->getHandle(), true);
    }

    if(_input->IsKeyDown(GLFW_KEY_W))
    {
        _cubeTransform.position.y += 0.01f * deltaTime;
    }
    if(_input->IsKeyReleased(GLFW_KEY_W))
    {
        _cubeTransform.position.y = 0.0f;
    }

    // TODO: Arcball cam
}

void App::Render()
{
    _input->SaveKeys();

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

void App::OnKeyPressed(int key, int action)
{
    // _input->UpdateKey(Key(key, action));

    bool state;

    if(action != GLFW_RELEASE)
    {
        state = true;
    }
    else
    {
        state = false;
    }

    _input->UpdateKey(key, state);
}