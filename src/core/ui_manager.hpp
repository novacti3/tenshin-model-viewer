#pragma once

#include <GLFW/glfw3.h>

class UIManager
{
    private:
    UIManager() = default;
    ~UIManager() = default;

    public:
    static void Init(GLFWwindow *window, const char *glslVersion);
    static void Render();
    static void Cleanup();
};