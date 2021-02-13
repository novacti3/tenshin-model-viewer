#include "renderer.hpp"

#include "core/log.hpp"
#include "components/transform_component.hpp"

#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

void RenderScene(const Scene &scene)
{
    GL_CALL(glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    // TODO: Make the clear color adjustable in the UI
    GL_CALL(glad_glClearColor(0.2f, 0.0f, 0.2f, 1.0f));

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
}