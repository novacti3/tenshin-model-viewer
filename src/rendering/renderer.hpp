#pragma once

#include "core/scene.hpp"

class Renderer
{
    private:
    // TODO: Resize framebuffer on window resize
    static unsigned int _framebuffer;
    static unsigned int _colorBuffer;
    static unsigned int _depthBuffer;

    public:
    static bool Init();
    static void Cleanup();

    static const unsigned int &getFramebuffer() { return _framebuffer; }

    // NOTE: maybe have it return a Texture object or whatever directly
    static void RenderScene(const Scene &scene);
};