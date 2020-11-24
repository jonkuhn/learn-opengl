#pragma once

#include <initializer_list>

#include "Shader.h"

namespace Graphics::OpenGL
{
    class ShaderProgram
    {
    public:
        ShaderProgram(std::initializer_list<Shader> shaders);
        ~ShaderProgram();

        GLuint Handle();

    private:
        GLuint _handle;
    };
}