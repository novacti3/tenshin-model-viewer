#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <vector>

struct Vertex
{
    glm::vec3 position;
    glm::vec2 uv;
    glm::vec3 normal;

    Vertex()
    {
        this->position = glm::vec3(0, 0, 0);
        this->uv = glm::vec2(0, 0);;
        this->normal = glm::vec3(0, 0, 0);;
    }
    Vertex(glm::vec3 position, glm::vec2 uv, glm::vec3 normal)
    {
        this->position = position;
        this->uv = uv;
        this->normal = normal;
    }

    ~Vertex(){}
};

struct Face
{
    glm::ivec3 indices;

    Face()
    {
        this->indices = glm::ivec3(0, 0, 0);
    }
    Face(glm::ivec3 indices)
    {
        this->indices = indices;
    }

    ~Face(){}
};

class Model
{
    private:
    std::vector<Vertex> _vertices;
    std::vector<Face> _faces;

    public:
    Model(std::vector<Vertex> vertices, std::vector<Face> faces)
        : _vertices(vertices), _faces(faces) {}
    ~Model(){}

    inline std::vector<Vertex> &getVertices() { return _vertices; }
    inline std::vector<Face> &getFaces() { return _faces; }
};