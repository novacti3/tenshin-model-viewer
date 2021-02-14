#pragma once

#include <glad/glad.h>
#include <glm/vec2.hpp>

class Texture
{
    public:
    void *data;

    private:
    unsigned int _id;
    int _target;
    glm::uvec2 _size;
    int _internalFormat;
    int _format;
    
    public:
    // TODO: Adjustable tex params
    Texture(int target, glm::uvec2 size, int internalFormat, int format, const void *data = nullptr);
    ~Texture();

    public:
    const unsigned int &getID() const { return _id; }

    void Bind() const;
    void Unbind() const;
};