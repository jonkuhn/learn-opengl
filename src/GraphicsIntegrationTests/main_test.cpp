#include <gtest/gtest.h>

// TODO: remove this
#include "Graphics/OpenGL/GlfwWrapper.h"
#include "Graphics/OpenGL/OpenGLWrapper.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  // TODO: remove this
  Graphics::OpenGL::GlfwWrapper glfw;
  InitializeGlfwAndGlad(glfw, 800, 600);

  return RUN_ALL_TESTS();
}