#include "app.hpp"

#include "log.hpp"
#include "resource_manager.hpp"

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
    
}

void App::Render()
{
    Quad rect(glm::vec3(-0.5, -0.5, 0.0f), glm::vec3(-0.5, 0.5, 0.0f), glm::vec3(0.5, -0.5, 0.0f), glm::vec3(0.5, 0.5, 0.0f));

    glad_glClear(GL_COLOR_BUFFER_BIT);
    glad_glClearColor(0.2f, 0.0f, 0.2f, 1.0f);

    rect.Draw(*ResourceManager::GetShader("unlit-color"), glm::vec3(0.0f, 0.0f, -5.0f), 45.0f, glm::vec3(1.0f, 1.0f, 0.0f));

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