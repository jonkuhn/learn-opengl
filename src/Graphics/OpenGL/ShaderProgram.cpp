#include "ShaderProgram.h"

#include <string>
#include <sstream>
#include <vector>


using namespace Graphics::OpenGL;

ShaderProgram::ShaderProgram(std::initializer_list<Shader> shaders)
{
    _handle = glCreateProgram();

    for(auto shader : shaders)
    {
        glAttachShader(_handle, shader.Handle());
    }

    glLinkProgram(_handle);

    // check for linking errors
    GLint success;
    glGetProgramiv(_handle, GL_LINK_STATUS, &success);
    if (!success) {
        GLint infoLogLength;
        glGetProgramiv(_handle, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<char> infoLog(infoLogLength);
        glGetProgramInfoLog(_handle, infoLog.size(), NULL, infoLog.data());
        std::stringstream ss;
        ss << "Shader Linking Failed: " << infoLog.data() << "" << std::endl;
        throw std::runtime_error(ss.str().c_str());
    }
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(_handle);
}

GLuint ShaderProgram::Handle()
{
    return _handle;
}