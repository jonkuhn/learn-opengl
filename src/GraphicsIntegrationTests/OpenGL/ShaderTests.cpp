#include <string>
#include <sstream>

#include <gtest/gtest.h>

#include "Graphics/OpenGL/Shader.h"
#include "Graphics/OpenGL/OpenGLWrapper.h"
#include "TestHelpers.h"

using namespace testing;
using namespace Graphics::OpenGL;

TEST(ShaderTests, CreateVertexShaderSuccess)
{
    OpenGLWrapper gl;

    EXPECT_NO_THROW(
        Shader shader(
            gl,
            Shader::Type::Vertex,
            GetValidVertexShaderCode());
        EXPECT_NE(shader.Handle(), (GLuint)0);
    );
}

TEST(ShaderTests, CreateFragmentShaderSuccess)
{
    OpenGLWrapper gl;

    EXPECT_NO_THROW(
        Shader shader(
            gl,
            Shader::Type::Fragment,
            GetValidFragmentShaderCode());
        EXPECT_NE(shader.Handle(), (GLuint)0);
    );
}

TEST(ShaderTests, CreateVertexShaderThrows)
{
    OpenGLWrapper gl;

    EXPECT_THROW(
        Shader shader(
            gl,
            Shader::Type::Vertex,
            "this is not valid code"),
        std::runtime_error
    );
}

TEST(ShaderTests, CreateFragmentShaderThrows)
{
    OpenGLWrapper gl;

    EXPECT_THROW(
        Shader shader(
            gl,
            Shader::Type::Fragment,
            "this is not valid code"),
        std::runtime_error
    );
}
