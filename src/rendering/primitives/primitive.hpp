#pragma once

#include "core/log.hpp"
#include "core/types.hpp"

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
    // Copy
    Primitive(const Primitive& other)
    {
        this->_vertices = other._vertices;
        this->_indices = other._indices;

        this->_VAO = other._VAO;
        this->_VBO = other._VBO;
        this->_EBO = other._EBO;
    }
    Primitive& operator=(Primitive other)
    {
        this->_vertices = other._vertices;
        this->_indices = other._indices;

        this->_VAO = other._VAO;
        this->_VBO = other._VBO;
        this->_EBO = other._EBO;
    
        return *this;
    }
    // Move
    Primitive(Primitive&& other)
    {
        this->_vertices = std::move(other._vertices);
        this->_indices = std::move(other._indices);

        this->_VAO = std::move(other._VAO);
        this->_VBO = std::move(other._VBO);
        this->_EBO = std::move(other._EBO);    
    }
    Primitive& operator=(Primitive&& other)
    {
        this->_vertices = std::move(other._vertices);
        this->_indices = std::move(other._indices);

        this->_VAO = std::move(other._VAO);
        this->_VBO = std::move(other._VBO);
        this->_EBO = std::move(other._EBO);

        return *this;
    }

    public:
    inline const std::vector<Vertex>       &getVertices() const { return _vertices; }
    inline const std::vector<unsigned int> &getIndices()  const { return _indices; }

    inline const unsigned int &getVAO() const { return _VAO; }
    inline const unsigned int &getVBO() const { return _VBO; }
    inline const unsigned int &getEBO() const { return _EBO; }
};