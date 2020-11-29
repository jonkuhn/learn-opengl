#include "ShaderProgram.h"

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

GLuint ShaderProgram::Handle()
{
    return _handle;
}