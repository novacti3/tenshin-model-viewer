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
std::function<void(Action&, glm::ivec2 value)> App::_onRotateCam;

bool App::Init(const glm::uvec2 windowSize, const std::string windowTitle)
{
    const char *glslVersion = "#version 330";
    // Create window
    if(!Window::getInstance().Init(windowSize, windowTitle))
    {
        Log::LogFatal("Failed initializing window");
        return false;
    }
    Log::LogInfo("Window initialized");
    // Window::AddListener(this);

    Input::getInstance().Init();
    Log::LogInfo("Input initialized");

    _onRotateCam = [this](Action &action, glm::ivec2 value)
    {
        App::OnRotateCam(action, value);
    };

    ButtonActionFunc quitProgramFunc = &QuitProgram;
    Input::getInstance().BindFuncToAction("QuitProgram", quitProgramFunc);
    Input::getInstance().BindFuncToAction("RotateCamera", _onRotateCam);

    _onKeyPressed = [this](int key, int action)
    {
        App::OnKeyPressed(key, action);
    };
    glfwSetKeyCallback(Window::getInstance().getHandle(), App::GLFWKeyCallback);

    SceneObject *camera = new SceneObject(new TransformComponent(glm::vec3(0.0f, 0.0f, 3.0f)));
    camera->AddComponent<CameraComponent>(new CameraComponent(*(camera->GetComponent<TransformComponent>()), 60.0f, (float)Window::getInstance().getSize().x/(float)Window::getInstance().getSize().y, 0.01f, 100.0f));
    _scenes.push_back(new Scene(camera));
    _currentScene = _scenes[0];

    if(!Renderer::Init())
    {
        Log::LogFatal("Failed initializing renderer");
        return false;
    }
    Log::LogInfo("Renderer initialized");

    if(!UIManager::Init(Window::getInstance().getHandle(), glslVersion))
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
    Input::getInstance().StoreKeys();

    // Render everything in the current Scene to a framebuffer so the UIManager can display it in the Scene window
    Renderer::RenderScene(*_currentScene);
    // Render UI
    UIManager::Render(Window::getInstance().getSize().x, Window::getInstance().getSize().y);

    // TODO: Set up a layer system to which stuff can be added that will get rendered in the order the layers are in
    // eg. Editor UI layer = 0 (topmost layer, gets rendered over everything), in-scene UI layer, scene layer etc.
    // TODO: Separate input between each layer

    glfwSwapBuffers(Window::getInstance().getHandle());
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
    Input::getInstance().Cleanup();

    // Clean up window and GLFW
    Window::getInstance().Cleanup();

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

    Input::getInstance().UpdateKey(key, state);
}

void App::QuitProgram(Action& action)
{
    glfwSetWindowShouldClose(Window::getInstance().getHandle(), true);
}

void App::OnRotateCam(Action &action, glm::ivec2 value)
{
    // FIXME: This is fucking horrible and needs to be changed to something more sane ASAP
    // Log::LogInfo(std::string("RotateCamera value:\n x: ") + std::to_string(value.x) + std::string("\n y: ") + std::to_string(value.y));

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

    // FIXME: There's a weird delay before the camera starts panning smoothly (eg. W is pressed, the camera moves up slightly, then there's a delay and only after the delay the camera starts to move up fluidly)
    TransformComponent *camTransform = const_cast<TransformComponent*>(_currentScene->FindObjectOfType<CameraComponent>()->GetComponent<TransformComponent>());
    glm::vec3 rot = glm::vec3(static_cast<float>(value.y) * ROT_SPEED, static_cast<float>(value.x) * ROT_SPEED, 0.0f);
    rot.x = glm::clamp(rot.x, MIN_PITCH, MAX_PITCH);
    camTransform->addRotation(rot);
}