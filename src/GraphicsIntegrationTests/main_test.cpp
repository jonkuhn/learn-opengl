#include <gtest/gtest.h>

// TODO: remove this
#include "Graphics/OpenGL/GlfwWrapper.h"
#include "Graphics/OpenGL/OpenGLWrapper.h"
#include "Graphics/OpenGL/Window.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  // TODO: remove this
  Graphics::OpenGL::GlfwWrapper glfw;
  Graphics::OpenGL::Window window(glfw, 800, 600, "DummyWindowForIntegrationTests");

  return RUN_ALL_TESTS();
}