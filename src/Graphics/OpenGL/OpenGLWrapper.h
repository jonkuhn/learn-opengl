#pragma once
#include "IOpenGLWrapper.h"

#include <mutex>
#include <sstream>

namespace Graphics::OpenGL
{
    class OpenGLWrapper : public IOpenGLWrapper
    {
    public:
        GLuint CreateShader(GLenum shaderType) override
        {
            return glCreateShader(shaderType);
        };

        void ShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length) override
        {
            glShaderSource(shader, count, string, length);
        };

        void CompileShader(GLuint shader) override
        {
            glCompileShader(shader);
        };

        void GetShaderiv(GLuint shader, GLenum pname, GLint* params) override
        {
            glGetShaderiv(shader, pname, params);
        }

        void GetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog) override
        {
            glGetShaderInfoLog(shader, maxLength, length, infoLog);
        }

        void DeleteShader(GLuint shader) override
        {
            glDeleteShader(shader);
        }
    };
}