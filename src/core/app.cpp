#include "app.hpp"

#include "log.hpp"
#include "resource_manager.hpp"

#include "../rendering/primitives/quad.hpp"
#include "../rendering/primitives/cube.hpp"

#include "../components/transform.hpp"
#include "../components/primitive_renderer.hpp"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

std::function<void(int, int)> App::_onKeyPressed;

bool App::Init(const glm::uvec2 windowSize, const std::string windowTitle)
{
    const char *glslVersion = "#version 330";
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
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    // TODO: Add ImGui docking support

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(_window->getHandle(), true);
    ImGui_ImplOpenGL3_Init(glslVersion);

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

    // NOTE: Perhaps move this camera code elsewhere
    // TODO: Add mouse camera movement (pan and zoom)
    static const float rotationSpeed = 1.0f;
    static float yaw = 0.0f;
    static float pitch = 0.0f;
    static const float MIN_PITCH = -90.0f;
    static const float MAX_PITCH = 90.0f;
    // static float elevationSpeed = 0.05f;
    static const float zoomSpeed = 0.05f;
    static float zoomAmount = 0.0f;
    static const float MIN_ZOOM = 0.5f;
    static const float MAX_ZOOM = 5.0f;

    // Move up
    // FIXME: Make the elevation move the camera along the world Y axis instead of the local Y axis
    // if(_input->IsKeyDown(GLFW_KEY_E) || _input->IsKeyDown(GLFW_KEY_KP_8))
    // {
    //     _cam->transform.addPosition(glm::vec3(0.0f, elevationSpeed, 0.0f));
    // }
    // // Move down
    // if(_input->IsKeyDown(GLFW_KEY_Q) || _input->IsKeyDown(GLFW_KEY_KP_2))
    // {
    //     _cam->transform.addPosition(glm::vec3(0.0f, -elevationSpeed, 0.0f));
    // }

    // Zoom in
    if(_input->IsKeyDown(GLFW_KEY_LEFT_SHIFT) || _input->IsKeyDown(GLFW_KEY_KP_ADD))
    {
        zoomAmount = _cam->transform.getPosition().z + zoomSpeed;
        zoomAmount = glm::clamp(zoomAmount, MIN_ZOOM, MAX_ZOOM);

        _cam->transform.setPosition(glm::vec3(_cam->transform.getPosition().x, _cam->transform.getPosition().y, zoomAmount));
    }
    // Zoom out
    if(_input->IsKeyDown(GLFW_KEY_LEFT_CONTROL) || _input->IsKeyDown(GLFW_KEY_KP_SUBTRACT))
    {
        zoomAmount = _cam->transform.getPosition().z - zoomSpeed;
        zoomAmount = glm::clamp(zoomAmount, MIN_ZOOM, MAX_ZOOM);

        _cam->transform.setPosition(glm::vec3(_cam->transform.getPosition().x, _cam->transform.getPosition().y, zoomAmount));
    }

    // Pitch up
    if(_input->IsKeyDown(GLFW_KEY_W) || _input->IsKeyDown(GLFW_KEY_UP))
    {
        pitch = _cam->transform.getRotation().x + (-rotationSpeed);
        pitch = glm::clamp(pitch, MIN_PITCH, MAX_PITCH);

        _cam->transform.setRotation(glm::vec3(pitch, _cam->transform.getRotation().y, _cam->transform.getRotation().z));
    }
    // Pitch down
    if(_input->IsKeyDown(GLFW_KEY_S) || _input->IsKeyDown(GLFW_KEY_DOWN))
    {
        pitch = _cam->transform.getRotation().x + rotationSpeed;
        pitch = glm::clamp(pitch, MIN_PITCH, MAX_PITCH);

        _cam->transform.setRotation(glm::vec3(pitch, _cam->transform.getRotation().y, _cam->transform.getRotation().z));
    }
    // Yaw left
    if(_input->IsKeyDown(GLFW_KEY_A) || _input->IsKeyDown(GLFW_KEY_LEFT))
    {
        _cam->transform.addRotation(glm::vec3(0.0f, -rotationSpeed, 0.0f));
    }
    // Yaw right
    if(_input->IsKeyDown(GLFW_KEY_D) || _input->IsKeyDown(GLFW_KEY_RIGHT))
    {
        _cam->transform.addRotation(glm::vec3(0.0f, rotationSpeed, 0.0f));
    }
}

void App::Render()
{
    _input->SaveKeys();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if(_showDemoWindow)
    {
        ImGui::ShowDemoWindow(&_showDemoWindow);
    }

    ImGui::Render();

    GL_CALL(glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CALL(glad_glClearColor(0.2f, 0.0f, 0.2f, 1.0f));

    static Cube cube;
    static PrimitiveRenderer cubeRenderer(&cube, ResourceManager::GetShader("unlit-color"));
    cubeRenderer.Draw(_cubeTransform, _cam->getViewMatrix(), _cam->getProjMatrix());

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(_window->getHandle());
}

void App::Cleanup()
{
    // Clean up internal engine stuff
    ResourceManager::Cleanup();

    // Clean up ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    // Clean up window and GLFW
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