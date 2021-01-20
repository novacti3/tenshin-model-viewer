#pragma once

#include <GLFW/glfw3.h>
#include <imgui.h>

class UIManager
{
    private:
    static inline const char *DOCKSPACE_ID = "EditorDockspace";

    static inline bool _showDemoWindow = false;
    static inline bool _showModelProperties = true;
    static inline bool _showMaterialProperties = true;
    static inline bool _showRendererProperties = true;
    static inline bool _showDebugConsole = true;
    static inline bool _showScene = true;

    static inline ImGuiWindowFlags _windowFlags;

    private:
    UIManager() = default;
    ~UIManager() = default;

    public:
    static void Init(GLFWwindow *window, const char *glslVersion);
    static void Render(unsigned int width, unsigned int height);
    static void Cleanup();

    private:
    static void ShowMenuBar();
    static void ShowModelProperties();
    static void ShowMaterialProperties();
    static void ShowRendererProperties();
    static void ShowDebugConsole();
    static void ShowScene();
};