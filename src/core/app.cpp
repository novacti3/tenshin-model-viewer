#include "app.hpp"

#include "core/log.hpp"
#include "core/resource_manager.hpp"
#include "core/ui_manager.hpp"
#include "rendering/renderer.hpp"

#include "components/transform_component.hpp"
#include "components/camera_component.hpp"
#include "components/primitive_renderer.hpp"
#include "rendering/primitives/cube.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

std::function<void(int, int)> App::_onKeyPressed;
std::function<void(Action&, glm::ivec2 value)> App::_rotateCam;

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

    _rotateCam = [this](Action &action, glm::ivec2 value)
    {
        App::RotateCamera(action, value);
    };

    ButtonActionFunc quitProgramFunc = &QuitProgram;
    Input::BindFuncToAction("QuitProgram", quitProgramFunc);
    // FIXME: Stack overflow presumably because of how the func pointer is (std::function)
    Input::BindFuncToAction("RotateCamera", _rotateCam);

    _onKeyPressed = [this](int key, int action)
    {
        App::OnKeyPressed(key, action);
    };
    glfwSetKeyCallback(Window::getHandle(), App::GLFWKeyCallback);

    SceneObject *camera = new SceneObject(new TransformComponent(glm::vec3(0.0f, 0.0f, -5.0f)));
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

    // FIXME: The transform values are flipped for some reason (eg. -Y is +Y although it should be +Y)
    // The rendering code might be scuffed because it appears that the camera moves and rotates ish rather than the individual cubes?
    SceneObject *cubeOne = new SceneObject(new TransformComponent(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
    cubeOne->AddComponent<PrimitiveRenderer>(new PrimitiveRenderer(new Cube(), ResourceManager::GetShader("unlit-color")));

    _currentScene->AddObject(cubeOne);
}

void App::Update(float deltaTime)
{

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

void App::RotateCam(Action &action, glm::ivec2 value)
{
    // FIXME: This is fucking horrible and needs to be changed to something more sane ASAP
    Log::LogInfo(std::string("RotateCamera value:\n x: ") + std::to_string(value.x) + std::string("\n y: ") + std::to_string(value.y));
    
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

    // TransformComponent &camTransform = *(const_cast<TransformComponent*>(_currentScene->FindObjectOfType<CameraComponent>()->GetComponent<TransformComponent>()));
    // glm::vec3 camRot = camTransform.getRotation();
    // camRot.x = glm::clamp((float)value.x * ROT_SPEED, MIN_PITCH, MAX_PITCH);
    // camRot.y = (float)value.y * ROT_SPEED;

    // camTransform.setRotation(camRot);
}