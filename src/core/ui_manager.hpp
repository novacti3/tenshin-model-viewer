#pragma once

#include "core/singleton.hpp"
#include "core/event.hpp"
#include "rendering/renderer.hpp"

#include <GLFW/glfw3.h>
#include <imgui.h>

class UIManager : public Singleton<UIManager>, public EventSender
{
    friend class Singleton<UIManager>;

    private:
    const char *DOCKSPACE_ID = "EditorDockspace";
    
    bool _showModelProperties = true;
    bool _showMaterialProperties = true;
    bool _showRendererProperties = true;
    bool _showDebugConsole = true;
    bool _showScene = true;

    ImGuiWindowFlags _windowFlags;

    private:
    UIManager() = default;
    ~UIManager() = default;

    public:
    bool Init(GLFWwindow *window, const char *glslVersion);
    void Render(unsigned int width, unsigned int height);
    void Cleanup();

    private:
    void ShowMenuBar();
    void ShowMaterialProperties();
    void ShowRendererProperties();
    void ShowDebugConsole();
    void ShowScene();
};