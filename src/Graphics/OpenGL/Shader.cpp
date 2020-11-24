#include <string>
#include <sstream>
#include <vector>

#include "./Shader.h"

using namespace Graphics::OpenGL;

namespace 
{
    using namespace Graphics::OpenGL;

    std::string readAllToString(std::istream& istream)
    {
        std::istreambuf_iterator<char> eos;
        return std::string(std::istreambuf_iterator<char>(istream), eos);
    }

    GLenum typeToShaderEnum(Shader::Type type)
    {
        switch (type)
        {
            case Shader::Type::Vertex: return GL_VERTEX_SHADER;
            case Shader::Type::Fragment: return GL_FRAGMENT_SHADER;
            default:
            {
                std::stringstream ss;
                ss << "Invalid shader type: " << static_cast<int>(type);
                throw std::invalid_argument(ss.str().c_str());
            }
        }
    }
}

Shader::Shader(Type type, std::istream& sourceCodeStream)
    : Shader(type, readAllToString(sourceCodeStream))
{

}

Shader::Shader(Type type, const std::string& source)
{
    const char* sourceCstr = source.c_str();

    _handle = glCreateShader(typeToShaderEnum(type));
    if (!_handle)
    {
        throw new std::runtime_error("glCreateShader failed");
    }

    glShaderSource(_handle, 1, &sourceCstr, nullptr);
    glCompileShader(_handle);

    int success;
    glGetShaderiv(_handle, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLint infoLogLength;
        glGetShaderiv(_handle, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<char> infoLog(infoLogLength);
        glGetShaderInfoLog(_handle, infoLog.size(), NULL, infoLog.data());
        std::stringstream ss;
        ss << "Shader Compilation Failed: " << infoLog.data() << "" << std::endl
            << "Shader Source:" << std::endl
            << source << std::endl;
        throw std::runtime_error(ss.str().c_str());
    }
}

Shader::~Shader()
{
    glDeleteShader(_handle);
}

GLuint Shader::Handle()
{
    return _handle;
}