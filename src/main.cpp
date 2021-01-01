#include "log.hpp"
#include "types.hpp"
#include "window.hpp"
#include "rendering/shader.hpp"
#include "resource_manager.hpp"
#include "app.hpp"

#include <glad/glad.h>

#include <array>

static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 600;
static const std::string WINDOW_TITLE = "Tenshin Model Viewer";

int main()
{
    // if(!Log::InitFileLog("../../debug_output.txt"))
    // {
    //     Log::LogWarning("Couldn't initialize file log");
    // }

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
        currentTime = glfwGetTime() / 1000;
        deltaTime = currentTime - lastTime;
        lastTime = deltaTime;

        app.PollInput(deltaTime);
        app.Update(deltaTime);
        app.Render();
    }

    app.Cleanup();

    return 0;
}