#include "window.hpp"

#include "log.hpp"

bool Window::Init(const glm::uvec2 size, const std::string title)
{
    _size = size;
    _title = title;

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // TODO: Add resize support
    glfwWindowHint(GLFW_RESIZABLE, false);
    glfwWindowHint(GLFW_FOCUS_ON_SHOW, true);

    _handle = glfwCreateWindow(size.x, size.y, title.c_str(), NULL, NULL);
    if(_handle == nullptr)
    {
        Log::LogFatal("Failed creating window");
        return false;
    }

    glfwMakeContextCurrent(_handle);

    return true;
}

void Window::Cleanup()
{
    glfwDestroyWindow(_handle);
    glfwTerminate();
}