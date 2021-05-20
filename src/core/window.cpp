#include "window.hpp"

#include "log.hpp"

static const unsigned int MIN_WINDOW_WIDTH = 640;
static const unsigned int MIN_WINDOW_HEIGHT = 480;

bool Window::Init(glm::uvec2 size, const std::string title)
{
    _size = std::move(size);
    _title = std::move(title);

    // Init GLFW
    if(!glfwInit())
    {
        Log::LogFatal("Failed initializing GLFW");
        return false;
    }
    Log::LogInfo("GLFW initialized");

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_FOCUSED, true);
    // TODO: Figure out how to properly scale the contents of the window so it's not all stretched and shit
    glfwWindowHint(GLFW_RESIZABLE, true);

    // Make sure the start size of the window is above the specified minimum dimensions
    if(_size.x < MIN_WINDOW_WIDTH)
    {
        _size.x = MIN_WINDOW_WIDTH;
    }
    if(_size.y < MIN_WINDOW_HEIGHT)
    {
        _size.y = MIN_WINDOW_HEIGHT;
    }

    // Create window and OpenGL context
    _handle = glfwCreateWindow(_size.x, _size.y, _title.c_str(), NULL, NULL);
    if(_handle == nullptr)
    {
        Log::LogFatal("Failed creating window");
        return false;
    }
    glfwMakeContextCurrent(_handle);

    // Init GLAD
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Log::LogFatal("Failed initializing GLAD");
        return false;
    }
    Log::LogInfo("GLAD initialized");
    
    GL_CALL(glad_glViewport(0, 0, _size.x, _size.y));

    glfwSetWindowSizeLimits(_handle, MIN_WINDOW_WIDTH, MIN_WINDOW_HEIGHT, GLFW_DONT_CARE, GLFW_DONT_CARE);
    // NOTE: Is limiting the aspect ratio even worth it?
    // TO DO: Make the window aspect ratio adjustable
    // glfwSetWindowAspectRatio(_handle, 16, 9);
    
    // Set up framebuffer resize callback
    // _onResize = [this](int width, int height)
    // {
    //     Window::OnResize(width, height);
    // };
    glfwSetFramebufferSizeCallback(_handle, Window::ResizeCallback);

    return true;
}

void Window::Cleanup()
{
    glfwDestroyWindow(_handle);
    Log::LogInfo("Window destroyed");

    glfwTerminate();
    Log::LogInfo("GLFW terminated");
}

void Window::ResizeCallback(GLFWwindow *window, int width, int height)
{
    Window::getInstance().setSize(glm::uvec2(width, height));
}