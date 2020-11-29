#pragma once
#include <gmock/gmock.h>

#include "Graphics/OpenGL/IOpenGLWrapper.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
class MockOpenGLWrapper : public Graphics::OpenGL::IOpenGLWrapper {
public:
    MOCK_METHOD(GLenum, GetError, (), (override));
    MOCK_METHOD(GLuint, CreateShader, (GLenum type), (override));
    MOCK_METHOD(void, ShaderSource, (GLuint shader, GLsizei count, const GLchar** string, const GLint* length), (override));
    MOCK_METHOD(void, CompileShader, (GLuint shader), (override));
    MOCK_METHOD(void, GetShaderiv, (GLuint shader, GLenum, GLint*), (override));
    MOCK_METHOD(void, GetShaderInfoLog, (GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog), (override));
    MOCK_METHOD(void, DeleteShader, (GLuint shader), (override));
    MOCK_METHOD(GLuint, CreateProgram, (), (override));
    MOCK_METHOD(void, AttachShader, (GLuint program, GLuint shader), (override));
    MOCK_METHOD(void, LinkProgram, (GLuint program), (override));
    MOCK_METHOD(void, GetProgramiv, (GLuint program, GLenum pname, GLint *params), (override));
    MOCK_METHOD(void, GetProgramInfoLog, (GLuint program, GLsizei maxLength, GLsizei* length, GLchar* infoLog), (override));
    MOCK_METHOD(void, DeleteProgram, (GLuint program), (override));
};
#pragma clang diagnostic pop