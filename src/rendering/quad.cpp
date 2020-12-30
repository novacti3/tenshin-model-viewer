#include "quad.hpp"

#include "../log.hpp"

#include <glad/glad.h>

Quad::Quad(const glm::vec3 bottomLeft, const glm::vec3 topLeft, const glm::vec3 bottomRight, const glm::vec3 topRight)
{
    _vertices = 
    {
        Vertex(topLeft,     glm::vec2(0.0f, 1.0f), glm::ivec3(0.0f)), // top left
        Vertex(bottomLeft,  glm::vec2(0.0f, 0.0f), glm::ivec3(0.0f)), // bottom left
        Vertex(bottomRight, glm::vec2(1.0f, 0.0f), glm::ivec3(0.0f)), // bottom right
        Vertex(topRight,    glm::vec2(1.0f, 1.0f), glm::ivec3(0.0f))  // top right
    };
    _indices =
    {
        0, 1, 2,
        2, 3, 0
    };

    GL_CALL(glad_glGenVertexArrays(1, &_VAO));
    GL_CALL(glad_glGenBuffers(1, &_VBO));
    GL_CALL(glad_glGenBuffers(1, &_EBO));

    GL_CALL(glad_glBindVertexArray(_VAO));

    GL_CALL(glad_glBindBuffer(GL_ARRAY_BUFFER, _VBO));
    GL_CALL(glad_glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), _vertices.data(), GL_STATIC_DRAW));

    GL_CALL(glad_glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (void*)0));
    GL_CALL(glad_glEnableVertexAttribArray(0));
    GL_CALL(glad_glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(Vertex), (void*)sizeof(glm::vec3)));
    GL_CALL(glad_glEnableVertexAttribArray(1));

    GL_CALL(glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO));
    GL_CALL(glad_glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned char), _indices.data(), GL_STATIC_DRAW));

    GL_CALL(glad_glBindVertexArray(0));
    GL_CALL(glad_glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL_CALL(glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

Quad::~Quad()
{
    GL_CALL(glad_glDeleteBuffers(1, &_EBO));
    GL_CALL(glad_glDeleteBuffers(1, &_VBO));
    GL_CALL(glad_glDeleteVertexArrays(1, &_VAO));
}

void Quad::Draw(Shader &shader)
{
    if(_VAO == 0 || _VBO == 0 || _EBO == 0)
    {
        // TODO: Add assert/log
        return;
    }

    shader.Bind();
    GL_CALL(glad_glBindVertexArray(_VAO));
    GL_CALL(glad_glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_BYTE, (void*)0));
    GL_CALL(glad_glBindVertexArray(0));
    shader.Unbind();
}