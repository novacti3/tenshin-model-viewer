#pragma once

#include "rendering/primitives/primitive.hpp"

#include <glm/vec3.hpp>

class Quad final : public Primitive
{
    public:
    Quad(const glm::vec3 bottomLeft, const glm::vec3 topLeft, const glm::vec3 bottomRight, const glm::vec3 topRight);
    ~Quad() = default;
};