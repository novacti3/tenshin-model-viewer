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
static const std::string WINDOW_TITLE = "Model Viewer";

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

    // TODO: Move to a Quad class
    std::array<Vertex, 4> vertices = 
    {
        Vertex(glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec2(0.0f, 1.0f), glm::ivec3(0.0f)), // top left
        Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f), glm::ivec3(0.0f)), // bottom left
        Vertex(glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f), glm::ivec3(0.0f)), // bottom right
        Vertex(glm::vec3( 0.5f,  0.5f, 0.0f), glm::vec2(1.0f, 1.0f), glm::ivec3(0.0f))  // top right
    };
    std::array<unsigned char, 2*3> indices =
    {
        0, 1, 2,
        2, 3, 0
    };
    unsigned int VAO, VBO, EBO;

    GL_CALL(glad_glGenVertexArrays(1, &VAO));
    GL_CALL(glad_glGenBuffers(1, &VBO));
    GL_CALL(glad_glGenBuffers(1, &EBO));

    GL_CALL(glad_glBindVertexArray(VAO));

    GL_CALL(glad_glBindBuffer(GL_ARRAY_BUFFER, VBO));
    GL_CALL(glad_glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW));

    GL_CALL(glad_glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (void*)0));
    GL_CALL(glad_glEnableVertexAttribArray(0));
    GL_CALL(glad_glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(Vertex), (void*)sizeof(glm::vec3)));
    GL_CALL(glad_glEnableVertexAttribArray(1));

    GL_CALL(glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
    GL_CALL(glad_glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW));

    GL_CALL(glad_glBindVertexArray(0));
    GL_CALL(glad_glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL_CALL(glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

    Shader *shader = ResourceManager::GetShader("unlit-color");

    float lastTime = 0, currentTime = 0, deltaTime = 0;
    while(!glfwWindowShouldClose(app.getWindow()->getHandle()))
    {
        // NOTE: Might want to move this into a static Time class or something so it's accessible from anywhere
        currentTime = glfwGetTime() / 1000;
        deltaTime = currentTime - lastTime;
        lastTime = deltaTime;

        app.PollInput(deltaTime);
        app.Update(deltaTime);
        // app.Render();

        glfwSwapBuffers(app.getWindow()->getHandle());

        // TODO: Move to App::Render
        glad_glClear(GL_COLOR_BUFFER_BIT);
        glad_glClearColor(0.2f, 0.0f, 0.2f, 1.0f);

        shader->Bind();
        GL_CALL(glad_glBindVertexArray(VAO));
        GL_CALL(glad_glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_BYTE, (void*)0));
        GL_CALL(glad_glBindVertexArray(0));
        shader->Unbind();
    }

    app.Cleanup();

    return 0;
}