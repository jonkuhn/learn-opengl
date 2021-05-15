#pragma once
#include <functional>
#include <istream>
#include <string>
#include <sstream>
#include <vector>

#include "IShader.h"
#include "OpenGLWrapper.h"
#include "UniqueHandle.h"

namespace Graphics::OpenGL
{
    class IOpenGLWrapper;

    enum class ShaderType
    {
        Vertex,
        Fragment
    };

    template<typename Tgl = OpenGLWrapper>
    class Shader final : public IShader
    {
    public:
        Shader(Tgl gl, ShaderType type, std::istream& sourceStream);
        Shader(Tgl gl, ShaderType type, const std::string& source);

        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;
        Shader(Shader&&) = default;
        Shader& operator=(Shader&&) = default;

        GLuint Handle() override;

    private:
        Tgl _gl;

        typedef UniqueHandle<std::function<void (IOpenGLWrapper*, GLuint)>> UniqueShaderHandle;
        UniqueShaderHandle _handle;

        static std::string ReadAllToString(std::istream& istream);
        static GLenum TypeToShaderEnum(ShaderType type);
    };
}

#include "Shader.ipp"
