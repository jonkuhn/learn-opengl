#include <string>
#include <sstream>

#include <gtest/gtest.h>

#include "Graphics/OpenGL/ShaderProgram.h"
#include "Graphics/OpenGL/Shader.h"
#include "Graphics/OpenGL/GlfwWrapper.h"
#include "Graphics/OpenGL/Window.h"
#include "Graphics/OpenGL/OpenGLWrapper.h"
#include "TestHelpers.h"

using namespace testing;
using namespace Graphics::OpenGL;

class ShaderProgramTests : public Test
{
public:
    ShaderProgramTests()
        : _gl(),
          _glfw(),
          _window(_glfw, 800, 600, "DummyIntegrationTestWindow")
    {

    }
protected:
    OpenGLWrapper _gl;
    GlfwWrapper _glfw;
    Window _window;
};

TEST_F(ShaderProgramTests, CreateShaderProgramSuccess)
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
