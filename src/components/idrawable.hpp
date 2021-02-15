#pragma once

#include "components/transform_component.hpp"

#include <glm/mat4x4.hpp>

class IDrawable
{
    protected:
    IDrawable() = default;
    virtual ~IDrawable() = default;

    public:
    virtual void Draw(const TransformComponent &transform, const glm::mat4 &viewMatrix, const glm::mat4 &projMatrix) const = 0;
};