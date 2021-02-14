#include "app.hpp"

#include "core/log.hpp"
#include "core/resource_manager.hpp"
#include "core/ui_manager.hpp"
#include "rendering/renderer.hpp"

#include "components/transform_component.hpp"
#include "components/camera_component.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

std::function<void(int, int)> App::_onKeyPressed;

bool App::Init(const glm::uvec2 windowSize, const std::string windowTitle)
{
    const char *glslVersion = "#version 330";
    // Create window
    if(!Window::Init(windowSize, windowTitle))
    {
        Log::LogFatal("Failed initializing window");
        return false;
    }
    Log::LogInfo("Window initialized");
    // Window::AddListener(this);

    Input::Init();
    Log::LogInfo("Input initialized");

    ButtonActionFunc quitProgramFunc = &QuitProgram;
    Input::BindFuncToAction("QuitProgram", quitProgramFunc);
    TwoDimensionalActionFunc rotateCamFunc = &RotateCamera;
    Input::BindFuncToAction("RotateCamera", rotateCamFunc);

    _onKeyPressed = [this](int key, int action)
    {
        App::OnKeyPressed(key, action);
    };
    glfwSetKeyCallback(Window::getHandle(), App::GLFWKeyCallback);
    
    SceneObject *camera = new SceneObject(new TransformComponent(glm::vec3(0.0f, 0.0f, 3.0f)));
    camera->AddComponent<CameraComponent>(new CameraComponent(*(camera->GetComponent<TransformComponent>()), 60.0f, (float)Window::getSize().x/(float)Window::getSize().y, 0.01f, 100.0f));
    _scenes.push_back(new Scene(camera));
    _currentScene = _scenes[0];

    if(!Renderer::Init())
    {
        Log::LogFatal("Failed initializing renderer");
        return false;
    }
    Log::LogInfo("Renderer initialized");

    if(!UIManager::Init(Window::getHandle(), glslVersion))
    {
        Log::LogFatal("Failed initializing UI manager");
    }
    Log::LogInfo("UI manager initialized");
    
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
    Input::StoreKeys();

    // Render everything in the current Scene to a framebuffer so the UIManager can display it in the Scene window
    Renderer::RenderScene(*_currentScene);
    // Render UI
    UIManager::Render(Window::getSize().x, Window::getSize().y);

    // TODO: Set up a layer system to which stuff can be added that will get rendered in the order the layers are in
    // eg. Editor UI layer = 0 (topmost layer, gets rendered over everything), in-scene UI layer, scene layer etc.
    // TODO: Separate input between each layer

    // static Cube cube;
    // static PrimitiveRenderer cubeRenderer(&cube, ResourceManager::GetShader("unlit-color"));
    // cubeRenderer.Draw(_cubeTransform, _cam->getViewMatrix(), _cam->getProjMatrix());

    glfwSwapBuffers(Window::getHandle());
}

void App::Cleanup()
{
    // Delete scenes
    for(Scene *scene: _scenes)
    {
        delete scene;
        scene = nullptr;
    }
    _currentScene = nullptr; 

    // Clean up internal engine stuff
    ResourceManager::Cleanup();
    Renderer::Cleanup();
    UIManager::Cleanup();    
    Input::Cleanup();

    // Clean up window and GLFW
    Window::Cleanup();

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

    Input::UpdateKey(key, state);
}

void App::QuitProgram(Action& action)
{
    glfwSetWindowShouldClose(Window::getHandle(), true);
}

void App::RotateCamera(Action &action, glm::ivec2 value)
{
    // FIXME: This is fucking horrible and needs to be changed to something more sane ASAP
    Log::LogInfo(std::string("RotateCamera value:\n x: ") + std::to_string(value.x) + std::string("\n y: ") + std::to_string(value.y));
}