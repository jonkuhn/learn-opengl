#pragma once
#include <istream>

#include "IShader.h"

namespace Graphics::OpenGL
{
    class IOpenGLWrapper;

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
        Shader(const Shader&) = delete;

        GLuint Handle() override;

    private:
        IOpenGLWrapper& _gl;
        GLuint _handle;
    };
}
