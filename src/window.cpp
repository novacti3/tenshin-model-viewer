#include "window.hpp"

#include "log.hpp"

std::function<void(int, int)> Window::_onResize;

static const unsigned int MIN_WINDOW_WIDTH = 640;
static const unsigned int MIN_WINDOW_HEIGHT = 360;

bool Window::Init(glm::uvec2 size, const std::string title)
{
    _size = size;
    _title = title;

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_FOCUS_ON_SHOW, true);
    glfwWindowHint(GLFW_RESIZABLE, true);

    // Make sure the start size of the window is above the specified minimum dimensions
    if(size.x < MIN_WINDOW_WIDTH)
    {
        size.x = MIN_WINDOW_WIDTH;
    }
    if(size.y < MIN_WINDOW_HEIGHT)
    {
        size.y = MIN_WINDOW_HEIGHT;
    }

    _handle = glfwCreateWindow(size.x, size.y, title.c_str(), NULL, NULL);
    if(_handle == nullptr)
    {
        Log::LogFatal("Failed creating window");
        return false;
    }

    glfwMakeContextCurrent(_handle);
    
    _onResize = [this](int width, int height)
    {
        Window::OnResize(width, height);
    };

    glfwSetWindowSizeLimits(_handle, MIN_WINDOW_WIDTH, MIN_WINDOW_HEIGHT, GLFW_DONT_CARE, GLFW_DONT_CARE);
    // NOTE: Is limiting the aspect ratio even worth it?
    // TO DO: Make the window aspect ratio adjustable
    // glfwSetWindowAspectRatio(_handle, 16, 9);
    
    glfwSetFramebufferSizeCallback(_handle, Window::ResizeCallback);

    return true;
}

void Window::Cleanup()
{
    glfwDestroyWindow(_handle);
    glfwTerminate();
}

void Window::OnResize(int width, int height)
{
    _size.x = width;
    _size.y = height;
    glad_glViewport(0, 0, width, height);
}