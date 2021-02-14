#include "texture.hpp"

#include "core/log.hpp"

Texture::Texture(int target, glm::uvec2 size, int internalFormat, int format, const void *data)
    : _target(std::move(target)), _size(std::move(size)), _internalFormat(std::move(internalFormat)), _format(std::move(format))
{
    this->data = const_cast<void*>(data);

    GL_CALL(glad_glGenTextures(1, &_id));
    Bind();
    GL_CALL(glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GL_CALL(glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GL_CALL(glad_glTexImage2D(_target, 0, _internalFormat, _size.x, _size.y, 0, _format, GL_UNSIGNED_BYTE, NULL));
    Unbind();
}
Texture::~Texture()
{
    GL_CALL(glad_glDeleteTextures(1, &_id));
} 

void Texture::Bind() const
{
    GL_CALL(glad_glBindTexture(_target, _id));
}
void Texture::Unbind() const
{
    GL_CALL(glad_glBindTexture(_target, 0));
}