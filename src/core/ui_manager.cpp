#include "ui_manager.hpp"

#include <imgui_internal.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

bool UIManager::Init(GLFWwindow *window, const char *glslVersion)
{
    IMGUI_CHECKVERSION();
    if(ImGui::CreateContext() == nullptr)
    {
        Log::LogFatal("Failed creating ImGui context");
        return false;
    }

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImColor(0.0f, 0.0f, 0.0f, 1.0f).Value);

    if(!ImGui_ImplGlfw_InitForOpenGL(window, true))
    {
        Log::LogFatal("Failed initializing ImGui GLFW backend");
        return false;
    }
    if(!ImGui_ImplOpenGL3_Init(glslVersion))
    {
        Log::LogFatal("Failed initializing ImGui OpenGL backend");
        return false;
    }

    _windowFlags = ImGuiWindowFlags_NoCollapse;

    return true;
}

void UIManager::Cleanup()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    Log::LogInfo("UI manager destroyed");
}

void UIManager::Render(unsigned int width, unsigned int height)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // TODO: Default layout
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
    
    // Menu bar
    ShowMenuBar();

    if(_showMaterialProperties)
    {
        ShowMaterialProperties();
    }

    if(_showRendererProperties)
    {
        ShowRendererProperties();
    }

    if(_showDebugConsole)
    {
        ShowDebugConsole();
    }

    if(_showScene)
    {
        ShowScene();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UIManager::ShowMenuBar()
{
    if(ImGui::BeginMainMenuBar())
    {
        if(ImGui::BeginMenu("File"))
        {
            if(ImGui::MenuItem("Load model in current tab..."))
            {

            }

            if(ImGui::MenuItem("Load model in new tab..."))
            {

            }

            ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("View"))
        {
            // TODO: Show a checkmark or something next to the menu item to indicate that the window is currently active in the editor

            if(ImGui::MenuItem("Show Material properties"))
            {
                _showMaterialProperties = !_showMaterialProperties;
            }

            if(ImGui::MenuItem("Show Rendering properties"))
            {
                _showRendererProperties = !_showRendererProperties;
            }

            if(ImGui::MenuItem("Show Debug console"))
            {
                _showDebugConsole = !_showDebugConsole;
            }

            if(ImGui::MenuItem("Show Scene"))
            {
                _showScene = !_showScene;
            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}

void UIManager::ShowMaterialProperties()
{
    ImGui::Begin("Material properties###MaterialProperties", &_showMaterialProperties, _windowFlags);
    {
        ImGui::Text("Material properties");
    }
    ImGui::End();
}

void UIManager::ShowRendererProperties()
{
    ImGui::Begin("Rendering properties###RenderingProperties", &_showRendererProperties, _windowFlags);
    {
        ImGui::Text("Renderer properties");
    }
    ImGui::End();
}

void UIManager::ShowDebugConsole()
{
    ImGui::Begin("Console###DebugConsole", &_showDebugConsole);
    {
        ImGui::Text("Debug console");
    }
    ImGui::End();
}

void UIManager::ShowScene()
{
    ImGui::Begin("Scene###SceneView", &_showScene, _windowFlags);
    {
        // TODO: Scale the texture to fit inside of the window
        ImGui::Image((void*)Renderer::getInstance().getColorBuffer().getID(), ImGui::GetWindowSize());
    }
    ImGui::End();
}