#include "ShaderProgram.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-volatile"
#include <glm/gtc/type_ptr.hpp>
#pragma clang diagnostic pop

#include <string>
#include <sstream>
#include <vector>


using namespace Graphics::OpenGL;

ShaderProgram::ShaderProgram(IOpenGLWrapper& gl, std::initializer_list<IShader*> shaders)
    : _gl(gl)
{
    if (shaders.size() == 0)
    {
        throw std::invalid_argument("No shaders passed to ShaderProgram.");
    }

    _handle = _gl.CreateProgram();
    if (!_handle)
    {
        std::stringstream ss;
        ss << "glCreateProgram failed with error: " << _gl.GetError();
        throw std::runtime_error(ss.str().c_str());
    }

    for(auto shader : shaders)
    {
        _gl.AttachShader(_handle, shader->Handle());
    }

    _gl.LinkProgram(_handle);

    // check for linking errors
    GLint success;
    _gl.GetProgramiv(_handle, GL_LINK_STATUS, &success);
    if (!success) {
        GLint infoLogLength;
        _gl.GetProgramiv(_handle, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<char> infoLog(infoLogLength);
        _gl.GetProgramInfoLog(_handle, infoLog.size(), NULL, infoLog.data());
        std::stringstream ss;
        ss << "Shader Program Linking Failed: " << infoLog.data() << "" << std::endl;
        throw std::runtime_error(ss.str().c_str());
    }
}

ShaderProgram::~ShaderProgram()
{
    _gl.DeleteProgram(_handle);
}

void ShaderProgram::Use()
{
    _gl.UseProgram(_handle);
}

void ShaderProgram::SetUniform(const std::string name, int value)
{
    _gl.Uniform1i(_gl.GetUniformLocation(_handle, name.c_str()), value);
}

void ShaderProgram::SetUniform(const std::string name, const glm::mat4& value)
{
    _gl.UniformMatrix4fv(
        _gl.GetUniformLocation(_handle, name.c_str()),
        1,
        false,
        glm::value_ptr(value));
}

void ShaderProgram::SetUniform(const std::string name, const glm::vec3& value)
{
    _gl.Uniform3fv(
        _gl.GetUniformLocation(_handle, name.c_str()),
        1,
        glm::value_ptr(value));
}