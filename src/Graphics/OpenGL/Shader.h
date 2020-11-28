#pragma once
#include <istream>

#include "IOpenGLWrapper.h"

namespace Graphics::OpenGL
{
    class Shader
    {
    public:
        enum class Type
        {
            Vertex,
            Fragment
        };

        Shader(IOpenGLWrapper& gl, Type type, std::istream& sourceStream);
        Shader(IOpenGLWrapper& gl, Type type, const std::string& source);
        ~Shader();

        GLuint Handle();

    private:
        IOpenGLWrapper& _gl;
        GLuint _handle;
    };
}