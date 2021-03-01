#include "renderer.hpp"

#include "core/log.hpp"
#include "core/window.hpp"
#include "components/transform_component.hpp"
#include "components/primitive_renderer.hpp"

#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

unsigned int Renderer::_framebuffer;
Texture *Renderer::_colorBuffer;
Texture *Renderer::_depthBuffer;

bool Renderer::Init()
{
    GL_CALL(glad_glGenFramebuffers(1, &_framebuffer));
    GL_CALL(glad_glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer));

    // Generate color buffer
    _colorBuffer = new Texture(GL_TEXTURE_2D, Window::getInstance().getSize(), GL_RGB8, GL_RGB);
    // Attach color buffer to framebuffer
    GL_CALL(glad_glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _colorBuffer->getID(), 0));

    // Generate depth buffer
    _depthBuffer = new Texture(GL_TEXTURE_2D, Window::getInstance().getSize(), GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT);
    // Attach depth buffer to framebuffer
    GL_CALL(glad_glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthBuffer->getID(), 0));

    // TODO: Add checks for more errors
    if(glad_glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        Log::LogError("Framebuffer incomplete");
        return false;
    }

    GL_CALL(glad_glBindFramebuffer(GL_FRAMEBUFFER, 0));
    return true;
}

void Renderer::Cleanup()
{
    GL_CALL(glad_glDeleteFramebuffers(1, &_framebuffer));
    delete _colorBuffer;
    _colorBuffer = nullptr;
    delete _depthBuffer;
    _depthBuffer = nullptr;

    Log::LogInfo("Renderer destroyed");
}

void Renderer::RenderScene(const Scene &scene)
{
    GL_CALL(glad_glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer)); 

    GL_CALL(glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    
    // TODO: Make the clear color adjustable in the UI
    GL_CALL(glad_glClearColor(0.2f, 0.0f, 0.2f, 1.0f));
    
    const SceneObject* camObj = scene.FindObjectOfType<CameraComponent>();
    if(camObj == nullptr)
    {
        Log::LogError("Cannot draw scene, no camera found");
        return;
    }
    CameraComponent &camera = *(const_cast<CameraComponent*>(camObj->GetComponent<CameraComponent>()));

    GL_CALL(glad_glEnable(GL_DEPTH_TEST));
    
    std::vector<const SceneObject*> drawableObjs = scene.FindObjectsOfType<IDrawable>();
    for(const SceneObject *drawableObj: drawableObjs)
    {
        drawableObj->GetComponent<IDrawable>()->Draw(*(drawableObj->GetComponent<TransformComponent>()), camera.getViewMatrix(*(camObj->GetComponent<TransformComponent>())), camera.getProjMatrix());
    }

    GL_CALL(glad_glDisable(GL_DEPTH_TEST));

    GL_CALL(glad_glBindFramebuffer(GL_FRAMEBUFFER, 0));
}