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
    // static unsigned int *_colorBufferData;
    // static unsigned int *_depthBufferData;

    public:
    static bool Init();
    static void Cleanup();

    static inline const unsigned int &getFramebuffer() { return _framebuffer; }
    static inline const Texture &getColorBuffer() { return *_colorBuffer; }
    static inline const Texture &getDepthBuffer() { return *_depthBuffer; }
    // static inline const void *getColorBufferData() { return _colorBufferData; }
    // static inline const void *getDepthBufferData() { return _depthBufferData; }

    // NOTE: maybe have it return a Texture object or whatever directly
    static void RenderScene(const Scene &scene);
};