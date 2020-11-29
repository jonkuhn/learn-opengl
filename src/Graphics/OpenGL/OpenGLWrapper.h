#pragma once
#include "IOpenGLWrapper.h"

#include <mutex>
#include <sstream>

namespace Graphics::OpenGL
{
    class OpenGLWrapper : public IOpenGLWrapper
    {
    public:
        GLenum GetError() override
        {
            return glGetError();
        }

        GLuint CreateShader(GLenum shaderType) override
        {
            return glCreateShader(shaderType);
        }

        void ShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length) override
        {
            glShaderSource(shader, count, string, length);
        }

        void CompileShader(GLuint shader) override
        {
            glCompileShader(shader);
        }

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

        GLuint CreateProgram() override
        {
            return glCreateProgram();
        }

        void AttachShader(GLuint program, GLuint shader) override
        {
            glAttachShader(program, shader);
        }

        void LinkProgram(GLuint program) override
        {
            glLinkProgram(program);
        }

        void GetProgramiv(GLuint program, GLenum pname, GLint *params) override
        {
            glGetProgramiv(program, pname, params);
        }

        void GetProgramInfoLog(GLuint program, GLsizei maxLength, GLsizei* length, GLchar* infoLog) override
        {
            glGetProgramInfoLog(program, maxLength, length, infoLog);
        }

        void DeleteProgram(GLuint program) override
        {
            glDeleteProgram(program);
        }
    };
}