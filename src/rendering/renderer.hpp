#pragma once

#include "core/singleton.hpp"
#include "core/scene.hpp"
#include "core/event.hpp"
#include "rendering/texture.hpp"

class Renderer : public Singleton<Renderer>, public EventListener
{
    friend class Singleton<Renderer>;

    private:
    // TODO: Resize framebuffer on window resize
    unsigned int _framebuffer;
    Texture *_colorBuffer;
    Texture *_depthBuffer;

    private:
    Renderer() = default;
    ~Renderer() = default;
    public:
    // Copy
    Renderer(const Renderer& other) = delete;
    Renderer& operator=(Renderer other) = delete;
    // Move
    Renderer(Renderer&& other) = delete;
    Renderer& operator=(Renderer&& other) = delete;

    public:
    bool Init();
    void Cleanup();

    inline const unsigned int &getFramebuffer() { return _framebuffer; }
    inline const Texture &getColorBuffer() { return *_colorBuffer; }
    inline const Texture &getDepthBuffer() { return *_depthBuffer; }
    
    // NOTE: maybe have it return a Texture object or whatever directly
    void RenderScene(const Scene &scene);

    private:
    void OnEvent(Event &event) override;
};