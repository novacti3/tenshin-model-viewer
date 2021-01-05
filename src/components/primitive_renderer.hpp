#pragma once

#include "../rendering/shader.hpp"
#include "../rendering/primitives/primitive.hpp"
#include "transform.hpp"

#include <glm/mat4x4.hpp>

class PrimitiveRenderer
{
    private:
    Primitive *_primitive;
    Shader *_shader;

    public:
    PrimitiveRenderer(Primitive *primitive, Shader *shader);
    ~PrimitiveRenderer();

    void Draw(const Transform &transform, const glm::mat4 &viewMatrix, const glm::mat4 &projMatrix);
};