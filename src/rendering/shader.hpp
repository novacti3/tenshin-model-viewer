#pragma once

class Shader
{
    private:
    unsigned int _id;

    public:
    Shader(const char *vertSource, const char *fragSource);
    ~Shader();

    public:
    void Bind() const;
    void Unbind() const;

    inline const unsigned int &getID() const { return _id; }

    private:
    void CheckShaderForErrors(unsigned int shader);
};