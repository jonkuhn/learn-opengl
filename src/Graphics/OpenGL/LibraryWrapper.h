#pragma once
#include "./ILibraryWrapper.h"

namespace Graphics::OpenGL
{
    class LibraryWrapper : public ILibraryWrapper
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