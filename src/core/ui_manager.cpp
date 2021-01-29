#include "ui_manager.hpp"

#include <imgui_internal.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

void UIManager::Init(GLFWwindow *window, const char *glslVersion)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImColor(0.0f, 0.0f, 0.0f, 1.0f).Value);

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glslVersion);

    _windowFlags = ImGuiWindowFlags_NoCollapse;
}

void UIManager::Cleanup()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
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

        if(ImGui::BeginMenu("Edit"))
        {
            if(ImGui::MenuItem("Preferences..."))
            {

            }

            ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("View"))
        {
            // TODO: Show a checkmark or something next to the menu item to indicate that the window is currently active in the editor

            if(ImGui::MenuItem("Show Model Properties"))
            {
                _showModelProperties = !_showModelProperties;
            }

            if(ImGui::MenuItem("Show Material Properties"))
            {
                _showMaterialProperties = !_showMaterialProperties;
            }

            if(ImGui::MenuItem("Show Renderer Properties"))
            {
                _showRendererProperties = !_showRendererProperties;
            }

            if(ImGui::MenuItem("Show Console"))
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
    ImGui::Begin("Material Properties###MaterialProperties", &_showMaterialProperties, _windowFlags);
    {
        ImGui::Text("Material properties");
    }
    ImGui::End();
}

void UIManager::ShowRendererProperties()
{
    ImGui::Begin("Renderer Properties###RendererProperties", &_showRendererProperties, _windowFlags);
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
        ImGui::Text("Scene window");
    }
    ImGui::End();
}