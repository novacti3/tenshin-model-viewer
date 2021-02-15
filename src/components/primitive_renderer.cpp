#include "primitive_renderer.hpp"

#include "core/log.hpp"

#include <glm/gtc/type_ptr.hpp>

PrimitiveRenderer::PrimitiveRenderer(Primitive *primitive, Shader *shader)
    : _primitive(primitive), _shader(shader){}
PrimitiveRenderer::~PrimitiveRenderer()
{
    _primitive = nullptr;
    _shader = nullptr;
}

void PrimitiveRenderer::Draw(const TransformComponent &objTransform, const glm::mat4 &viewMatrix, const glm::mat4 &projMatrix) const
{
    if(_primitive->getVAO() == 0 || _primitive->getVBO() == 0)
    {
        // NOTE: Adding a line number and/or file would be cool
        Log::LogWarning("Attempting to draw uninitialized primitive");
        return;
    }

    glm::mat4 modelMatrix = objTransform.CalculateModelMatrix();

    glm::mat4 MVP = projMatrix * viewMatrix * modelMatrix;

    _shader->Bind();
    GL_CALL(glad_glBindVertexArray(_primitive->getVAO()));
    GL_CALL(glad_glUniformMatrix4fv(glad_glGetUniformLocation(_shader->getID(), "u_MVP"), 1, false, glm::value_ptr(MVP)));
    
    // Draw the index buffer if available
    // NOTE: Might want to make it so the draw type is adjustable (eg. GL_LINES instead of GL_TRIANGLES for wireframe view)
    if(_primitive->getEBO() != 0)
    {
        const auto indices = _primitive->getIndices();
        GL_CALL(glad_glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data()));
    }
    else
    {
        const auto vertices = _primitive->getVertices();
        GL_CALL(glad_glDrawArrays(GL_TRIANGLES, 0, vertices.size()));
    }

    GL_CALL(glad_glBindVertexArray(0));
    _shader->Unbind();
}