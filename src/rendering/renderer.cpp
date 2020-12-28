#include "renderer.hpp"

#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Renderer::DrawModel(Model *model, Shader *shader, const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale)
{
    GL_CALL(glad_glEnable(GL_CULL_FACE));
    GL_CALL(glad_glCullFace(GL_BACK));

    // MVP matrix
    glm::mat4 transform = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    transform = glm::translate(transform, position);
    transform = glm::scale(transform, scale);

    projection = glm::perspective(glm::radians(90.0f), (float)800/(float)600, 0.1f, 100.0f);

    glm::mat4 MVP = projection * view * transform;

    // Drawing
    GL_CALL(glad_glBindVertexArray(model->getVAO()));
    shader->Bind();
    GL_CALL(glad_glUniformMatrix4fv(glad_glGetUniformLocation(shader->getID(), "u_MVP"), 1, false, glm::value_ptr(MVP)));
    // GL_CALL(glad_glDrawArrays(GL_TRIANGLES, 0, model->getVertices().size()));
    GL_CALL(glad_glDrawElements(GL_TRIANGLES, model->getFaces().size() * 2 * 3, GL_UNSIGNED_INT, 0));
    shader->Unbind();
    GL_CALL(glad_glBindVertexArray(0));
}