#pragma once

#include "rendering/texture.hpp"
#include "core/scene.hpp"

class Renderer
{
    private:
    // TODO: Resize framebuffer on window resize
    static unsigned int _framebuffer;
    static Texture *_colorBuffer;
    static Texture *_depthBuffer;

    public:
    static bool Init();
    static void Cleanup();

    static const unsigned int &getFramebuffer() { return _framebuffer; }
    static const Texture &getColorBuffer() { return *_colorBuffer; }
    static const Texture &getDepthBuffer() { return *_depthBuffer; }

    // NOTE: maybe have it return a Texture object or whatever directly
    static void RenderScene(const Scene &scene);
};