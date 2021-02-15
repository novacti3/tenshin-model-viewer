#pragma once

#include "scene_object.hpp"
#include "components/camera_component.hpp"

#include <vector>

// NOTE: Maybe move the function definitions to a cpp file

class Scene
{
    private:
    std::vector<SceneObject*> _sceneObjects;
    // NOTE: Shortcut for the camera?

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
    inline const std::vector<SceneObject*> &getSceneObjects() const { return _sceneObjects; }
    // NOTE: Find object by name func?
    
    void AddObject(SceneObject *obj)
    {
        _sceneObjects.push_back(obj);
    }
    void RemoveObject(SceneObject *obj)
    {
        // NOTE: Doing this is probably inefficient because to get the object pointer, you must loop through the scene objects already and now loop through them again to get the iterator
        // Making the SceneObjects vector changeable directly might be better?
        for (auto i = _sceneObjects.begin(); i < _sceneObjects.end(); i++)
        {
            if(obj == *i)
            {
                _sceneObjects.erase(i);
            }
        }
    }

    template<class T>
    const SceneObject* FindObjectOfType() const
    {
        for(const SceneObject *obj: _sceneObjects)
        {
            if(obj->GetComponent<T>() != nullptr)
            {
                return obj;
            }
        }

        return nullptr;
    }    
    // TODO: Clean this up
    template<class T>
    std::vector<const SceneObject*> FindObjectsOfType() const
    {
        std::vector<const SceneObject*> compObjects;

        for(const SceneObject *obj: _sceneObjects)
        {
            const T *comp = obj->GetComponent<T>();
            if(comp != nullptr)
            {
                compObjects.push_back(obj);
            }
        }

        return compObjects;
    }
};