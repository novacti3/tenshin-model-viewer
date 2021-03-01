#include "core/log.hpp"
#include "core/types.hpp"
#include "core/window.hpp"
#include "rendering/shader.hpp"
#include "core/resource_manager.hpp"
#include "core/app.hpp"

#include <glad/glad.h>

#include <array>

static const unsigned int WINDOW_WIDTH = 1600;
static const unsigned int WINDOW_HEIGHT = 1200;
static const std::string WINDOW_TITLE = "Tenshin Model Viewer";

int main()
{
#ifdef _DEBUG
    Log::SetLogLevelFilter(LogLevel::Info);
#else
    Log::SetLogLevelFilter(LogLevel::Error);
#endif

    App app;
    if(!app.Init(glm::uvec2(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE))
    {
        Log::LogFatal("Failed creating app instance");
        return -1;
    }
    Log::LogInfo("App instance created");

    app.LoadResources();

    float lastTime = 0, currentTime = 0, deltaTime = 0;
    while(!glfwWindowShouldClose(Window::getInstance().getHandle()))
    {
        // FIXME: The way the deltaTime is calculated must be goofd because it makes everything spazz out and anything but consistent and constant
        // NOTE: Might want to move this into a static Time class or something so it's accessible from anywhere
        currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = deltaTime;

        glfwPollEvents();
        app.Update(deltaTime);
        app.Render();
    }

    app.Cleanup();

    return 0;
}