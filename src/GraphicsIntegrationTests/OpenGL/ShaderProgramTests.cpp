#include <string>
#include <sstream>

#include <gtest/gtest.h>

#include "Graphics/OpenGL/ShaderProgram.h"
#include "Graphics/OpenGL/Shader.h"
#include "Graphics/OpenGL/OpenGLWrapper.h"
#include "TestHelpers.h"

using namespace testing;
using namespace Graphics::OpenGL;

TEST(ShaderProgramTests, CreateShaderProgramSuccess)
{
    OpenGLWrapper gl;

    Shader vertexShader(gl, Shader::Type::Vertex, GetValidVertexShaderCode());
    Shader fragmentShader(gl, Shader::Type::Fragment, GetValidFragmentShaderCode());
    EXPECT_NO_THROW(
        ShaderProgram shaderProgram(gl, {&vertexShader, &fragmentShader});
        EXPECT_NE(shaderProgram.Handle(), (GLuint)0)
    );
}

// In the future maybe write a test that intentionally
// produces a linking error if I figure out a reliable
// way to get compilation to succeed but linking to fail.
