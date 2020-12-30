#include "window.hpp"

#include "log.hpp"

bool Window::Init(const glm::uvec2 size, const std::string title)
{
    _size = size;
    _title = title;

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_FOCUS_ON_SHOW, true);
    glfwWindowHint(GLFW_RESIZABLE, true);

    _handle = glfwCreateWindow(size.x, size.y, title.c_str(), NULL, NULL);
    if(_handle == nullptr)
    {
        Log::LogFatal("Failed creating window");
        return false;
    }

    glfwMakeContextCurrent(_handle);
    
    // TODO: Make the minimum window size adjustable
    glfwSetWindowSizeLimits(_handle, size.x, size.y, GLFW_DONT_CARE, GLFW_DONT_CARE);
    // TODO: Make the window aspect ratio adjustable
    glfwSetWindowAspectRatio(_handle, 16, 9);
    glfwSetFramebufferSizeCallback(_handle, &(Window::ResizeWindowCallback));

    return true;
}

void Window::Cleanup()
{
    glfwDestroyWindow(_handle);
    glfwTerminate();
}

void Window::ResizeWindowCallback(GLFWwindow *window, int width, int height)
{
    // _size.x = width;
    // _size.y = height;
    glad_glViewport(0, 0, width, height);
}