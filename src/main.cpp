#include "core/log.hpp"
#include "core/types.hpp"
#include "core/window.hpp"
#include "rendering/shader.hpp"
#include "core/resource_manager.hpp"
#include "core/app.hpp"

#include <glad/glad.h>

#include <array>

static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 600;
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
    while(!glfwWindowShouldClose(app.getWindow()->getHandle()))
    {
        // NOTE: Might want to move this into a static Time class or something so it's accessible from anywhere
        currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = deltaTime;

        app.PollInput(deltaTime);
        app.Update(deltaTime);
        app.Render();
    }

    app.Cleanup();

    return 0;
}