#include "app.hpp"

#include "resource_manager.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void App::Init(Window *window)
{
    _window = window;

    ResourceManager::AddShader(ResourceManager::CreateShaderFromFiles("../../res/shaders/unlit-color.vs", "../../res/shaders/unlit-color.fs"), "unlit-color");
}

void App::PollInput(float deltaTime)
{

}

void App::Update(float deltaTime)
{
    glfwPollEvents();

    // TODO: Move to renderer
    glad_glClear(GL_COLOR_BUFFER_BIT);
    glad_glClearColor(0.2f, 0.0f, 0.2f, 1.0f);

    glfwSwapBuffers(_window->getHandle());
}

void App::Render()
{

}

void App::Cleanup()
{
    ResourceManager::Cleanup();

    _window->Cleanup();
    delete _window;
    _window = 0;
}