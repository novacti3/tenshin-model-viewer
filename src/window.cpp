#include "window.hpp"

#include "log.hpp"

bool Window::Init(const unsigned int width, const unsigned int height, const std::string title)
{
    _width = width;
    _height = height;
    _title = title;

    if(!glfwInit())
    {
        Log::LogFatal("Failed initializing GLFW");
        return false;
    }
    Log::LogInfo("GLFW initialized");

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // TODO: Add resize support
    glfwWindowHint(GLFW_RESIZABLE, false);
    glfwWindowHint(GLFW_FOCUS_ON_SHOW, true);

    _handle = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    glfwMakeContextCurrent(_handle);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Log::LogFatal("Failed initializing GLAD");
        return false;
    }
    Log::LogInfo("GLAD initialized");

    return true;
}

void Window::Cleanup()
{
    glfwDestroyWindow(_handle);
    glfwTerminate();
}