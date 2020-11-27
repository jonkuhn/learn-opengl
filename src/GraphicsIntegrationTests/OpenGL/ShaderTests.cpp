#include <string>
#include <sstream>

#include <gtest/gtest.h>

#include "Graphics/OpenGL/Shader.h"

using namespace testing;
using namespace Graphics::OpenGL;

namespace
{
    std::string GetValidVertexShaderCode()
    {
        return R"##RAW##(
            #version 330 core
            layout (location = 0) in vec3 aPos;
            void main()
            {
               gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
            }
            )##RAW##";
    }

    std::string GetValidFragmentShaderCode()
    {
        return R"##RAW##(
            #version 330 core
            out vec4 FragColor;
            void main()
            {
               FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
            }
            )##RAW##";
    }
}

TEST(ShaderTests, CreateVertexShaderSuccess)
{
    LibraryWrapper glLib;

    EXPECT_NO_THROW(
        Shader shader(
            glLib,
            Shader::Type::Vertex,
            GetValidVertexShaderCode());
        EXPECT_NE(shader.Handle(), (GLuint)0);
    );
}

TEST(ShaderTests, CreateFragmentShaderSuccess)
{
    LibraryWrapper glLib;

    EXPECT_NO_THROW(
        Shader shader(
            glLib,
            Shader::Type::Fragment,
            GetValidFragmentShaderCode());
        EXPECT_NE(shader.Handle(), (GLuint)0);
    );
}

TEST(ShaderTests, CreateVertexShaderThrows)
{
    LibraryWrapper glLib;

    EXPECT_THROW(
        Shader shader(
            glLib,
            Shader::Type::Vertex,
            "this is not valid code"),
        std::runtime_error
    );
}

TEST(ShaderTests, CreateFragmentShaderThrows)
{
    LibraryWrapper glLib;

    EXPECT_THROW(
        Shader shader(
            glLib,
            Shader::Type::Fragment,
            "this is not valid code"),
        std::runtime_error
    );
}
