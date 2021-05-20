#pragma once

#include "core/scene_object.hpp"
#include "components/camera_component.hpp"

#include <vector>

class Scene
{
    private:
    std::vector<SceneObject*> _sceneObjects;
    // NOTE: Shortcut for the camera?

    public:
    Scene();
    Scene(SceneObject *camera);
    ~Scene();
    // Copy
    Scene(const Scene& other);
    Scene& operator=(Scene other);
    // Move
    Scene(Scene&& other);
    Scene& operator=(Scene&& other);

    public:
    inline const std::vector<SceneObject*> &getSceneObjects() const { return _sceneObjects; }
    
    void AddObject(SceneObject *obj);
    void RemoveObject(SceneObject *obj);

    // NOTE: Find object by name func?
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