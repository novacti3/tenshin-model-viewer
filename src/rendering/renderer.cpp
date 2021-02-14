#include "renderer.hpp"

#include "core/log.hpp"
#include "components/transform_component.hpp"

#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

unsigned int Renderer::_framebuffer;
unsigned int Renderer::_colorBuffer;
unsigned int Renderer::_depthBuffer;

bool Renderer::Init()
{
    GL_CALL(glad_glGenFramebuffers(1, &_framebuffer));
    GL_CALL(glad_glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer));

    // Generate color buffer
    GL_CALL(glad_glGenTextures(1, &_colorBuffer));
    GL_CALL(glad_glBindTexture(GL_TEXTURE_2D, _colorBuffer));
    GL_CALL(glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GL_CALL(glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    // TODO: Replace with the current window size
    GL_CALL(glad_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 1600, 1200, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL));
    GL_CALL(glad_glBindTexture(GL_TEXTURE_2D, 0));
    // Attach color buffer to framebuffer
    GL_CALL(glad_glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _colorBuffer, 0));

    // // Generate depth buffer
    // GL_CALL(glad_glGenTextures(1, &_depthBuffer));
    // GL_CALL(glad_glBindTexture(GL_TEXTURE_2D, _depthBuffer));
    // // TODO: Replace with the current window size
    // GL_CALL(glad_glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, 1600, 1200, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL));
    // // Attach depth buffer to framebuffer
    // GL_CALL(glad_glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthBuffer, 0));
    // GL_CALL(glad_glBindTexture(GL_TEXTURE_2D, 0));

    // NOTE: Maybe add checks for more errors
    if(glad_glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        Log::LogInfo("Framebuffer incomplete");
        return false;
    }

    GL_CALL(glad_glBindFramebuffer(GL_FRAMEBUFFER, 0));
    return true;
}

void Renderer::Cleanup()
{
    GL_CALL(glad_glDeleteFramebuffers(1, &_framebuffer));
    GL_CALL(glad_glDeleteTextures(1, &_colorBuffer));
    GL_CALL(glad_glDeleteTextures(1, &_depthBuffer));
}

void Renderer::RenderScene(const Scene &scene)
{
    GL_CALL(glad_glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer)); 

    // GL_CALL(glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CALL(glad_glClear(GL_COLOR_BUFFER_BIT));
    
    // GL_CALL(glad_glEnable(GL_DEPTH_TEST));
    // TODO: Make the clear color adjustable in the UI
    GL_CALL(glad_glClearColor(0.2f, 0.0f, 0.2f, 1.0f));
    // GL_CALL(glad_glDisable(GL_DEPTH_TEST));

    GL_CALL(glad_glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

    
    // TODO: Render to framebuffer

    // if(scene.getCube()->getVAO() == 0 || scene.getCube()->getVBO() == 0)
    // {
    //     // NOTE: Adding a line number and/or file would be cool
    //     Log::LogWarning("Attempting to draw uninitialized primitive");
    //     return;
    // }

    // glm::mat4 modelMatrix = transform.CalculateModelMatrix();

    // glm::mat4 MVP = projMatrix * viewMatrix * modelMatrix;

    // _shader->Bind();
    // GL_CALL(glad_glBindVertexArray(scene.getCube()->getVAO()));
    // GL_CALL(glad_glUniformMatrix4fv(glad_glGetUniformLocation(_shader->getID(), "u_MVP"), 1, false, glm::value_ptr(MVP)));
    
    // // Draw the index buffer if available
    // // NOTE: Might want to make it so the draw type is adjustable (eg. GL_LINES instead of GL_TRIANGLES for wireframe view)
    // if(scene.getCube()->getEBO() != 0)
    // {
    //     const auto indices = scene.getCube()->getIndices();
    //     GL_CALL(glad_glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data()));
    // }
    // else
    // {
    //     const auto vertices = scene.getCube()->getVertices();
    //     GL_CALL(glad_glDrawArrays(GL_TRIANGLES, 0, vertices.size()));
    // }

    // GL_CALL(glad_glBindVertexArray(0));
    // _shader->Unbind();