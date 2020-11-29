#pragma once
#include <istream>

#include "IShader.h"
#include "IOpenGLWrapper.h"

namespace Graphics::OpenGL
{
    class Shader : public IShader
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

        GLuint Handle() override;

    private:
        IOpenGLWrapper& _gl;
        GLuint _handle;
    };
}