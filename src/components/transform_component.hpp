#pragma once

#include "components/icomponent.hpp"

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct TransformComponent final : public IComponent
{
    private:
    glm::vec3 _position;
    glm::vec3 _rotation;
    glm::vec3 _scale;

    public:
    TransformComponent(const glm::vec3 position = glm::vec3(0.0f), const glm::vec3 rotation = glm::vec3(0.0f), const glm::vec3 scale = glm::vec3(1.0f))
        : _position(std::move(position)), _rotation(std::move(rotation)), _scale(std::move(scale)){}
    ~TransformComponent(){}

    public:
    glm::mat4 CalculateModelMatrix() const
    {
        glm::mat4 model = glm::mat4(1.0f);

        model = glm::scale(model, _scale);
        // Yaw (Y axis)
        model = glm::rotate(model, glm::radians(_rotation.y), GetWorldUpVector());
        // Roll (Z axis)
        model = glm::rotate(model, glm::radians(_rotation.z), GetWorldForwardVector());
        // Pitch (X axis)
        model = glm::rotate(model, glm::radians(_rotation.x), GetWorldRightVector());

        model = glm::translate(model, _position);

        return model;
    }

    inline const glm::vec3 &getPosition() const { return _position; }
    inline const glm::vec3 &getRotation() const { return _rotation; }
    inline const glm::vec3 &getScale()    const { return _scale; }

    inline const glm::vec3 &setPosition(const glm::vec3 newPosition)
    {
        _position = newPosition; 
        return _position; 
    }
    inline const glm::vec3 &setRotation(const glm::vec3 newRotation) 
    { 
        _rotation = newRotation;
        
        // Clamp rotation between -360 and 360 degrees
        if(_rotation.x >= 360 || _rotation.x <= -360)
        {
            _rotation.x = 0;
        }
        if(_rotation.y >= 360 || _rotation.y <= -360)
        {
            _rotation.y = 0;
        }
        if(_rotation.z >= 360 || _rotation.z <= -360)
        {
            _rotation.z = 0;
        }

        return _rotation; 
    }
    inline const glm::vec3 &setScale(const glm::vec3 newScale)
    {
        _scale = newScale; 
        return _scale; 
    }

    inline const glm::vec3 &addPosition(const glm::vec3 newPosition)
    {
        _position += newPosition; 
        return _position; 
    }
    inline const glm::vec3 &addRotation(const glm::vec3 newRotation) 
    { 
        _rotation += newRotation;
        
        // Clamp rotation between -360 and 360 degrees
        if(_rotation.x >= 360 || _rotation.x <= -360)
        {
            _rotation.x = 0;
        }
        if(_rotation.y >= 360 || _rotation.y <= -360)
        {
            _rotation.y = 0;
        }
        if(_rotation.z >= 360 || _rotation.z <= -360)
        {
            _rotation.z = 0;
        }

        return _rotation; 
    }
    inline const glm::vec3 &addScale(const glm::vec3 newScale)
    {
        _scale += newScale; 
        return _scale; 
    }

    static inline glm::vec3 GetWorldForwardVector() { return glm::vec3(0.0f, 0.0f, -1.0f); }
    static inline glm::vec3   GetWorldRightVector() { return glm::vec3(1.0f, 0.0f, 0.0f); }
    static inline glm::vec3      GetWorldUpVector() { return glm::vec3(0.0f, 1.0f, 0.0f); }
};