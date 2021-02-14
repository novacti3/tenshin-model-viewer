#pragma once

#include "rendering/texture.hpp"
#include "core/scene.hpp"
#include "core/event.hpp"

class Renderer : public EventListener
{
    private:
    // TODO: Resize framebuffer on window resize
    static unsigned int _framebuffer;
    static Texture *_colorBuffer;
    static Texture *_depthBuffer;

    public:
    static bool Init();
    static void Cleanup();

    static inline const unsigned int &getFramebuffer() { return _framebuffer; }
    static inline const Texture &getColorBuffer() { return *_colorBuffer; }
    static inline const Texture &getDepthBuffer() { return *_depthBuffer; }

    // NOTE: maybe have it return a Texture object or whatever directly
    static void RenderScene(const Scene &scene);
};