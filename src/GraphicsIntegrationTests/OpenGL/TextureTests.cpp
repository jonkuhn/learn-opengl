#include <string>
#include <sstream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Graphics/PngImage.h"
#include "Graphics/LibPngWrapper.h"

#include "Graphics/OpenGL/GlfwWrapper.h"
#include "Graphics/OpenGL/Window.h"
#include "Graphics/OpenGL/OpenGLWrapper.h"
#include "Graphics/OpenGL/Texture.h"

using namespace testing;
using namespace Graphics::OpenGL;
using LibPngWrapper = Graphics::LibPngWrapper;
using PngImage = Graphics::PngImage;

class TextureTests : public Test
{
public:
    TextureTests()
        : _libpng(),
          _glfw(),
          _window(_glfw, 800, 600, "DummyIntegrationTestWindow"),
          _gl(_window)
    {
        // clear errors
        _gl.GetError();
    }
protected:
    LibPngWrapper _libpng;
    GlfwWrapper _glfw;
    GlfwWindow _window;
    OpenGLWrapper _gl;
};

TEST_F(TextureTests, CreateBindAndDestroyTexture)
{
    EXPECT_NO_THROW(
        PngImage image(_libpng, "TestFiles/test31x47.png");
        Texture texture(
            _gl,
            Texture::Params(image)
                .WrapModeS(Texture::WrapMode::Repeat)
                .WrapModeT(Texture::WrapMode::ClampToBorder)
                .MinFilter(Texture::MinFilterMode::NearestMipmapNearest)
                .MagFilter(Texture::MagFilterMode::Linear));

        texture.Bind();
    );
}
