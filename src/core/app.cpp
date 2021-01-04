#include "app.hpp"

#include "log.hpp"
#include "resource_manager.hpp"

#include "../rendering/primitives/quad.hpp"
#include "../rendering/primitives/cube.hpp"
#include "../rendering/primitive_renderer.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

    _cam = new Camera();

    return true;
}

void App::LoadResources()
{
    ResourceManager::AddShader(ResourceManager::CreateShaderFromFiles("../../res/shaders/unlit-color.vs", "../../res/shaders/unlit-color.fs"), "unlit-color");
}

void App::PollInput(float deltaTime)
{
    glfwPollEvents();
}

void App::Update(float deltaTime)
{
    _cam->UpdatePos(glfwGetTime());
}

void App::Render()
{
    Cube cube;
    PrimitiveRenderer cubeRenderer(&cube, ResourceManager::GetShader("unlit-color"));

    glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glad_glClearColor(0.2f, 0.0f, 0.2f, 1.0f);

    cubeRenderer.Draw(Transform(glm::vec3(0.0f), glm::vec3(1.0f)), _cam->getViewMatrix(), _cam->getProjMatrix());

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