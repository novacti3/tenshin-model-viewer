#include "shader.hpp"

#include <glad/glad.h>

void Shader::Init(const char *vertSource, const char *fragSource)
{
    unsigned int vertShader, fragShader;
    
    vertShader = glad_glCreateShader(GL_VERTEX_SHADER);
    glad_glShaderSource(vertShader, 1, &vertSource, 0);
    glad_glCompileShader(vertShader);

    fragShader = glad_glCreateShader(GL_FRAGMENT_SHADER);
    glad_glShaderSource(fragShader, 1, &fragSource, 0);
    glad_glCompileShader(fragShader);

    _id = glad_glCreateProgram();
    glad_glAttachShader(_id, vertShader);
    glad_glAttachShader(_id, fragShader);
    glad_glLinkProgram(_id);

    glad_glDeleteShader(vertShader);
    glad_glDeleteShader(fragShader);
}

void Shader::Cleanup()
{
    glad_glDeleteProgram(_id);
}


void Shader::Bind()
{
    glad_glUseProgram(_id);
}

void Shader::Unbind()
{
    glad_glUseProgram(0);
}