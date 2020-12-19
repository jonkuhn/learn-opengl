#pragma once
#include <glad/glad.h>

namespace Graphics::OpenGL
{
    class IOpenGLWrapper
    {
    public:
        virtual GLenum GetError() = 0;

        virtual GLuint CreateShader(GLenum shaderType) = 0;
        virtual void ShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length) = 0;
        virtual void CompileShader(GLuint shader) = 0;
        virtual void GetShaderiv(GLuint shader, GLenum pname, GLint* params) = 0;
        virtual void GetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog) = 0;
        virtual void DeleteShader(GLuint shader) = 0;

        virtual GLuint CreateProgram() = 0;
        virtual void AttachShader(GLuint program, GLuint shader) = 0;
        virtual void LinkProgram(GLuint program) = 0;
        virtual void GetProgramiv(GLuint program, GLenum pname, GLint *params) = 0;
        virtual void GetProgramInfoLog(GLuint program, GLsizei maxLength, GLsizei* length, GLchar* infoLog) = 0;
        virtual void DeleteProgram(GLuint program) = 0;
        virtual void UseProgram(GLuint program) = 0;
        virtual GLint GetUniformLocation(GLuint program, const GLchar* location) = 0;
        virtual void Uniform1i(GLint location, GLint v0) = 0;
        virtual void UniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) = 0;
        virtual void Uniform3fv(GLint location, GLsizei count, const GLfloat *value) = 0;

        virtual void GenVertexArrays(GLsizei n, GLuint* arrays) = 0;

        virtual void GenTextures(GLsizei n, GLuint* textures) = 0;
        virtual void DeleteTextures(GLsizei n, const GLuint* textures) = 0;

        virtual void BindTexture(GLenum target, GLuint texture) = 0;
        virtual void TexParameteri(GLenum target, GLenum pname, GLint param) = 0;
        virtual void TexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width,
            GLsizei height, GLint border, GLenum format, GLenum type, const void * data) = 0;

    };
}