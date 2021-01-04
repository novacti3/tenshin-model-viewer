#pragma once

#include "../../core/log.hpp"
#include "../../core/types.hpp"

#include <glad/glad.h>
#include <vector>

class Primitive
{
    protected:
    std::vector<Vertex> _vertices;
    std::vector<unsigned int> _indices;
    unsigned int _VAO, _VBO, _EBO;

    protected:
    Primitive() : _VAO(0), _VBO(0), _EBO(0) {}
    public:
    virtual ~Primitive()
    {
        GL_CALL(glad_glDeleteVertexArrays(1, &_VAO));
        GL_CALL(glad_glDeleteBuffers(1, &_VBO));
        GL_CALL(glad_glDeleteBuffers(1, &_EBO));
    }

    public:
    inline const std::vector<Vertex> &getVertices() { return _vertices; }
    inline const std::vector<unsigned int> &getIndices() { return _indices; }

    inline const unsigned int &getVAO() { return _VAO; }
    inline const unsigned int &getVBO() { return _VBO; }
    inline const unsigned int &getEBO() { return _EBO; }
};