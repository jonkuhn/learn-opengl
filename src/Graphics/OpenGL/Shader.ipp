#pragma once

namespace Graphics::OpenGL
{
    template<typename Tgl>
    Shader<Tgl>::Shader(Tgl gl, ShaderType type, std::istream& sourceCodeStream)
        : Shader(gl, type, ReadAllToString(sourceCodeStream))
    {

    }

    template<typename Tgl>
    Shader<Tgl>::Shader(Tgl gl, ShaderType type, const std::string& source)
        : _gl(gl),
          _handle(
              &_gl,
              _gl.CreateShader(TypeToShaderEnum(type)),
              [](IOpenGLWrapper* gl, GLuint h){ gl->DeleteShader(h); })
    {
        const char* sourceCstr = source.c_str();

        if (!_handle.get())
        {
            std::stringstream ss;
            ss << "glCreateShader failed with error: " << _gl.GetError();
            throw std::runtime_error(ss.str().c_str());
        }

        _gl.ShaderSource(_handle.get(), 1, &sourceCstr, nullptr);
        _gl.CompileShader(_handle.get());

        int success;
        _gl.GetShaderiv(_handle.get(), GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GLint infoLogLength;
            _gl.GetShaderiv(_handle.get(), GL_INFO_LOG_LENGTH, &infoLogLength);
            std::vector<char> infoLog(infoLogLength);
            _gl.GetShaderInfoLog(_handle.get(), infoLog.size(), NULL, infoLog.data());
            std::stringstream ss;
            ss << "Shader Compilation Failed: " << infoLog.data() << "" << std::endl
                << "Shader Source:" << std::endl
                << source << std::endl;
            throw std::runtime_error(ss.str().c_str());
        }
    }

    template<typename Tgl>
    GLuint Shader<Tgl>::Handle()
    {
        return _handle.get();
    }

    template<typename Tgl>
    std::string Shader<Tgl>::ReadAllToString(std::istream& istream)
    {
        std::istreambuf_iterator<char> eos;
        return std::string(std::istreambuf_iterator<char>(istream), eos);
    }

    template<typename Tgl>
    GLenum Shader<Tgl>::TypeToShaderEnum(ShaderType type)
    {
        switch (type)
        {
            case ShaderType::Vertex: return GL_VERTEX_SHADER;
            case ShaderType::Fragment: return GL_FRAGMENT_SHADER;
            default:
            {
                std::stringstream ss;
                ss << "Invalid shader type: " << static_cast<int>(type);
                throw std::invalid_argument(ss.str().c_str());
            }
        }
    }


}
