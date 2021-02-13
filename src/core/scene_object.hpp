#pragma once

#include "core/log.hpp"
#include "components/icomponent.hpp"
#include "components/transform_component.hpp"

#include <vector>

class SceneObject
{
    protected:
    std::vector<IComponent*> _components;

    public:
    TransformComponent transform;

    public:
    SceneObject(TransformComponent transform)
    {
        this->transform = std::move(transform);
    }
    ~SceneObject() = default;

    public:
    // TODO: Add component func
    template <class T>
    void AddComponent(T *component)
    {
        // Only add component if the type derives from IComponent (at least I hope this is what the line does)
        if(dynamic_cast<IComponent*>(component) != nullptr)
        {
            Log::LogError("Cannot add component: type doesn't inherit from IComponent");
            return;
        }

        _components.push_back(component);
    }
    
    // TODO: Remove component func
    template <class T>
    void RemoveComponent()
    {
        // Loop through all of the components and erase the component of the desired type 
        for (auto i = _components.begin(); i < _components.end(); i++)
        {
            if(dynamic_cast<T*>(*i) == component)
            {
                _components.erase(i);
                break;
            }
        }
    }

    // TODO: Get component func
    template <class T>
    void GetComponent()
    {

    }
};