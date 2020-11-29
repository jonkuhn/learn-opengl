#pragma once
#include <glad/glad.h>

namespace Graphics::OpenGL
{
    class IShader
    {
    public:
        virtual GLuint Handle() = 0;
    };
}