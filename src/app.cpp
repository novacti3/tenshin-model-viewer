#include "app.hpp"

#include "resource_manager.hpp"
#include "rendering/renderer.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void App::Init(Window *window)
{
    _window = window;

    ResourceManager::AddShader(ResourceManager::CreateShaderFromFiles("../../res/shaders/unlit-color.vs", "../../res/shaders/unlit-color.fs"), "unlit-color");

    ResourceManager::AddModel(ResourceManager::CreateModelFromOBJFile("../../res/models/cube.obj"), "cube");
    // ResourceManager::AddModel(ResourceManager::CreateModelFromOBJFile("../../res/models/axe.obj"), "axe");
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
    Renderer::DrawModel(ResourceManager::GetModel("cube"), ResourceManager::GetShader("unlit-color"), glm::vec3(0.0f, 0.0f, -40.0f), glm::vec3(0.0f), glm::vec3(30.0f));
    // Renderer::DrawModel(ResourceManager::GetModel("axe"), ResourceManager::GetShader("unlit-color"), glm::vec3(0.0f, 0.0f, -40.0f), glm::vec3(0.0f), glm::vec3(30.0f));
}

void App::Cleanup()
{
    ResourceManager::Cleanup();

    _window->Cleanup();
    delete _window;
    _window = 0;
}