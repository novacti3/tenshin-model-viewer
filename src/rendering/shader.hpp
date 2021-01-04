#pragma once

class Shader
{
    private:
    unsigned int _id;

    public:
    Shader(const char *vertSource, const char *fragSource);
    ~Shader();

    public:
    void Bind();
    void Unbind();

    inline const unsigned int getID() { return _id; }

    private:
    void CheckShaderForErrors(unsigned int shader);
};