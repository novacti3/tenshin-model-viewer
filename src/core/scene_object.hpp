#pragma once

#include "core/log.hpp"
#include "components/icomponent.hpp"
#include "components/transform_component.hpp"

#include <vector>

// NOTE: Maybe move the function definitions to a cpp file

class SceneObject
{
    protected:
    std::vector<IComponent*> _components;
    // TODO: Shortcut for the transform component would probably be cool

    public:
    SceneObject(TransformComponent *transform)
    {
        AddComponent(transform);
    }
    ~SceneObject() = default;

    public:
    template <class T>
    void AddComponent(T *component)
    {
        // Only add component if the type derives from IComponent
        if(!std::is_base_of<IComponent, T>::value)
        {
            Log::LogError("Cannot add component: type doesn't inherit from IComponent");
            return;
        }

        _components.push_back(component);
    }
    
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

    template <class T>
    const T *GetComponent() const
    {
        // Loop through all of the components and return the desired component if it's present
        for (auto i = _components.begin(); i < _components.end(); i++)
        {
            T* component = dynamic_cast<T*>(*i);
            if(component != nullptr)
            {
                return component;
            }
        }

        return nullptr;
    }
};