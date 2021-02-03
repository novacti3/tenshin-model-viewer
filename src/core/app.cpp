#include "app.hpp"

#include "core/log.hpp"
#include "core/resource_manager.hpp"
#include "core/ui_manager.hpp"

#include "rendering/primitives/quad.hpp"
#include "rendering/primitives/cube.hpp"

#include "components/transform.hpp"
#include "components/primitive_renderer.hpp"

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
    _window->AddListener(this);

    _input = new Input();
    ButtonActionFunc quitProgramFunc = &QuitProgram;
    _input->BindFuncToAction("QuitProgram", quitProgramFunc);
    TwoDimensionalActionFunc rotateCamFunc = &RotateCamera;
    _input->BindFuncToAction("RotateCamera", rotateCamFunc);

    _cam = new Camera(Transform(glm::vec3(0.0f, 0.0f, 3.0f)), 60.0f, (float)_window->getSize().x/(float)_window->getSize().y, 0.01f, 100.0f);

    _onKeyPressed = [this](int key, int action)
    {
        App::OnKeyPressed(key, action);
    };
    glfwSetKeyCallback(_window->getHandle(), App::GLFWKeyCallback);
    
    UIManager::Init(_window->getHandle(), glslVersion);

    return true;
}

void App::LoadResources()
{
    ResourceManager::AddShader(ResourceManager::CreateShaderFromFiles("../../res/shaders/unlit-color.vs", "../../res/shaders/unlit-color.fs"), "unlit-color");
}

void App::Update(float deltaTime)
{
    // if(_input->IsKeyPressed(GLFW_KEY_ESCAPE))
    // {
    //     glfwSetWindowShouldClose(_window->getHandle(), true);
    // }

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

    // // Zoom in
    // if(_input->IsKeyDown(GLFW_KEY_LEFT_SHIFT) || _input->IsKeyDown(GLFW_KEY_KP_ADD))
    // {
    //     zoomAmount = _cam->transform.getPosition().z - zoomSpeed;
    //     zoomAmount = glm::clamp(zoomAmount, MIN_ZOOM, MAX_ZOOM);

    //     _cam->transform.setPosition(glm::vec3(_cam->transform.getPosition().x, _cam->transform.getPosition().y, zoomAmount));
    // }
    // // Zoom out
    // if(_input->IsKeyDown(GLFW_KEY_LEFT_CONTROL) || _input->IsKeyDown(GLFW_KEY_KP_SUBTRACT))
    // {
    //     zoomAmount = _cam->transform.getPosition().z + zoomSpeed;
    //     zoomAmount = glm::clamp(zoomAmount, MIN_ZOOM, MAX_ZOOM);

    //     _cam->transform.setPosition(glm::vec3(_cam->transform.getPosition().x, _cam->transform.getPosition().y, zoomAmount));
    // }

    // // Pitch up
    // if(_input->IsKeyDown(GLFW_KEY_W) || _input->IsKeyDown(GLFW_KEY_UP))
    // {
    //     pitch = _cam->transform.getRotation().x + (-rotationSpeed);
    //     pitch = glm::clamp(pitch, MIN_PITCH, MAX_PITCH);

    //     _cam->transform.setRotation(glm::vec3(pitch, _cam->transform.getRotation().y, _cam->transform.getRotation().z));
    // }
    // // Pitch down
    // if(_input->IsKeyDown(GLFW_KEY_S) || _input->IsKeyDown(GLFW_KEY_DOWN))
    // {
    //     pitch = _cam->transform.getRotation().x + rotationSpeed;
    //     pitch = glm::clamp(pitch, MIN_PITCH, MAX_PITCH);

    //     _cam->transform.setRotation(glm::vec3(pitch, _cam->transform.getRotation().y, _cam->transform.getRotation().z));
    // }
    // // Yaw left
    // if(_input->IsKeyDown(GLFW_KEY_A) || _input->IsKeyDown(GLFW_KEY_LEFT))
    // {
    //     _cam->transform.addRotation(glm::vec3(0.0f, -rotationSpeed, 0.0f));
    // }
    // // Yaw right
    // if(_input->IsKeyDown(GLFW_KEY_D) || _input->IsKeyDown(GLFW_KEY_RIGHT))
    // {
    //     _cam->transform.addRotation(glm::vec3(0.0f, rotationSpeed, 0.0f));
    // }
}

void App::Render()
{
    _input->StoreKeys();

    // TODO: Make an event system (eg. have an OnOpenFilePressed event that pings the ResourceManager to load a model and return a OnFileOpened event that does other stuff)
    // TODO: Set up a layer system to which stuff can be added that will get rendered in the order the layers are in
    // eg. Editor UI layer = 0 (topmost layer, gets rendered over everything), in-scene UI layer, scene layer etc.
    // TODO: Separate input between each layer
    GL_CALL(glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CALL(glad_glClearColor(0.2f, 0.0f, 0.2f, 1.0f));
    
    static Cube cube;
    static PrimitiveRenderer cubeRenderer(&cube, ResourceManager::GetShader("unlit-color"));
    cubeRenderer.Draw(_cubeTransform, _cam->getViewMatrix(), _cam->getProjMatrix());

    UIManager::Render(_window->getSize().x, _window->getSize().y);

    glfwSwapBuffers(_window->getHandle());
}

void App::Cleanup()
{
    ButtonActionFunc quitProgramFunc = &QuitProgram;
    _input->UnbindFuncFromAction("QuitProgram", quitProgramFunc);
    TwoDimensionalActionFunc rotateCamFunc = &RotateCamera;
    _input->UnbindFuncFromAction("RotateCamera", rotateCamFunc);

    // Clean up internal engine stuff
    ResourceManager::Cleanup();
    UIManager::Cleanup();
    
    delete _input;
    _input = nullptr;

    delete _cam;
    _cam = nullptr;

    // Clean up window and GLFW
    _window->Cleanup();
    delete _window;
    _window = nullptr;

    Log::LogInfo("App instance destroyed");
}

void App::OnEvent(Event &event)
{
    if(event.getType() == EventType::WINDOW_RESIZED_EVENT)
    {
        Log::LogInfo("Window resize event fired");
    }
}

void App::OnKeyPressed(int key, int action)
{
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

void App::QuitProgram(Action& action)
{
    // TODO: Quit the program
    Log::LogInfo("QuitProgram action fired");
}

void App::RotateCamera(Action &action, glm::ivec2 value)
{
    // FIXME: This is fucking horrible and needs to be changed to something more sane ASAP
    Log::LogInfo(std::string("RotateCamera value:\n x: ") + std::to_string(value.x) + std::string("\n y: ") + std::to_string(value.y));
}