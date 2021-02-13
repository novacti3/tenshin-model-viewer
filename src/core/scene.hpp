#pragma once

#include "scene_object.hpp"
#include "components/camera_component.hpp"

#include <vector>

class Scene
{
    private:
    std::vector<SceneObject*> _sceneObjects;

    public:
    Scene()
    {
        SceneObject *camObject = new SceneObject(new TransformComponent(glm::vec3(0.0f, 0.0f, 3.0f)));
        camObject->AddComponent<CameraComponent>(new CameraComponent(*(camObject->GetComponent<TransformComponent>()), 60.0f, 1600.0f/1200.0f, 0.01f, 100.0f));      

        _sceneObjects.push_back(camObject);  
    }
    Scene(SceneObject *camera) 
    { 
        _sceneObjects.push_back(camera);   
    }
    ~Scene()
    {
        for(SceneObject *obj: _sceneObjects)
        {
            delete obj;
            obj = nullptr;
        }
    }

    public:
    inline const std::vector<SceneObject*> getSceneObjects() const { return _sceneObjects; }
    // NOTE: Find object by name func?
    // NOTE: Find object of type func?
    // NOTE: Find objects of type func?
};