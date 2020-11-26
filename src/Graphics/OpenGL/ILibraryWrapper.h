#pragma once
#include <glad/glad.h>

namespace Graphics::OpenGL
{
    class ILibraryWrapper
    {
    public:
        virtual GLuint CreateShader(GLenum shaderType) = 0;
        virtual void ShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length) = 0;
        virtual void CompileShader(GLuint shader) = 0;
        virtual void GetShaderiv(GLuint shader, GLenum pname, GLint* params) = 0;
        virtual void GetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog) = 0;
        virtual void DeleteShader(GLuint shader) = 0;
    };
}