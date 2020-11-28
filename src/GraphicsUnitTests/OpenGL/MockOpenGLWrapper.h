#pragma once
#include <gmock/gmock.h>

#include "Graphics/OpenGL/IOpenGLWrapper.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
class MockOpenGLWrapper : public Graphics::OpenGL::IOpenGLWrapper {
public:
    MOCK_METHOD(GLuint, CreateShader, (GLenum type), (override));
    MOCK_METHOD(void, ShaderSource, (GLuint shader, GLsizei count, const GLchar** string, const GLint* length), (override));
    MOCK_METHOD(void, CompileShader, (GLuint shader), (override));
    MOCK_METHOD(void, GetShaderiv, (GLuint shader, GLenum, GLint*), (override));
    MOCK_METHOD(void, GetShaderInfoLog, (GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog), (override));
    MOCK_METHOD(void, DeleteShader, (GLuint shader), (override));
};
#pragma clang diagnostic pop