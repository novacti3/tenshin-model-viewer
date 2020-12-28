#pragma once

#include <glad/glad.h>
#include "../log.hpp"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <vector>

struct Vertex
{
    glm::vec3 position;
    glm::vec2 uv;
    glm::ivec3 normal;

    Vertex()
    {
        this->position = glm::vec3(0.0f);
        this->uv = glm::vec2(0.0f);
        this->normal = glm::ivec3(0);
    }
    Vertex(glm::vec3 position, glm::vec2 uv, glm::ivec3 normal)
    {
        this->position = position;
        this->uv = uv;
        this->normal = normal;
    }
    ~Vertex(){}
};

struct Face
{
    glm::uvec3 firstTriangleIndices;
    glm::uvec3 secondTriangleIndices;

    Face()
    {
        this->firstTriangleIndices = glm::uvec3(0);
        this->secondTriangleIndices = glm::uvec3(0);
    }
    Face(glm::uvec3 firstTriangleIndices, glm::uvec3 secondTriangleIndices)
    {
        this->firstTriangleIndices = firstTriangleIndices;
        this->secondTriangleIndices = secondTriangleIndices;    
    }
    ~Face(){}
};

class Model
{
    private:
    unsigned int _VAO;
    unsigned int _VBO;
    unsigned int _EBO;
    std::vector<Vertex> _vertices;
    std::vector<Face> _faces;

    public:
    Model(std::vector<Vertex> vertices, std::vector<Face> faces)
        : _vertices(vertices), _faces(faces) 
    {
        GL_CALL(glad_glGenVertexArrays(1, &_VAO));
        GL_CALL(glad_glGenBuffers(1, &_VBO));
        GL_CALL(glad_glGenBuffers(1, &_EBO));

        GL_CALL(glad_glBindVertexArray(_VAO));

        // VBO
        GL_CALL(glad_glBindBuffer(GL_ARRAY_BUFFER, _VBO));
        GL_CALL(glad_glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), _vertices.data(), GL_STATIC_DRAW));

        // Vertex attribs
        GL_CALL(glad_glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), 0));
        GL_CALL(glad_glEnableVertexAttribArray(0));

        // EBO
        GL_CALL(glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO));
        GL_CALL(glad_glBufferData(GL_ELEMENT_ARRAY_BUFFER, _faces.size() * sizeof(Face), _faces.data(), GL_STATIC_DRAW));

        GL_CALL(glad_glBindVertexArray(0));
        GL_CALL(glad_glBindBuffer(GL_ARRAY_BUFFER, 0));
        GL_CALL(glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }
    ~Model()
    {
        _vertices.clear();
        _faces.clear();
        glad_glDeleteBuffers(1, &_VBO);
        glad_glDeleteBuffers(1, &_EBO);
        glad_glDeleteVertexArrays(1, &_VAO);
    }

    inline std::vector<Vertex> &getVertices() { return _vertices; }
    inline std::vector<Face> &getFaces() { return _faces; }
    inline unsigned int &getVAO() { return _VAO; }
    inline unsigned int &getVBO() { return _VBO; }
    inline unsigned int &getEBO() { return _EBO; }
};