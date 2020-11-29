#pragma once

#include <initializer_list>

#include "IShader.h"
#include "IOpenGLWrapper.h"

namespace Graphics::OpenGL
{
    class ShaderProgram
    {
    public:
        ShaderProgram(IOpenGLWrapper& gl, std::initializer_list<IShader*> shaders);
        ~ShaderProgram();

        GLuint Handle();

    private:
        IOpenGLWrapper& _gl;
        GLuint _handle;
    };
}