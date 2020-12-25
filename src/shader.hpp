#pragma once

class Shader
{
    private:
    unsigned int _id;

    public:
    Shader(){}
    ~Shader(){}

    public:
    void Init(const char *vertSource, const char *fragSource);
    void Cleanup();

    void Bind();
    void Unbind();

    inline unsigned int getID() { return _id; }
};