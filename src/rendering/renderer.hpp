#pragma once

#include "core/scene.hpp"

class Renderer
{
    public:
    // NOTE: maybe have it return a Texture object or whatever directly
    static void RenderScene(const Scene &scene);
};