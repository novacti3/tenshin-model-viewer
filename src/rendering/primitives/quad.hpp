#pragma once

#include "primitive.hpp"

#include <glm/vec3.hpp>

class Quad : public Primitive
{
    public:
    Quad(const glm::vec3 bottomLeft, const glm::vec3 topLeft, const glm::vec3 bottomRight, const glm::vec3 topRight);
    ~Quad();
};