#include <gtest/gtest.h>

// TODO: remove this
#include "Graphics/OpenGL/GlfwWrapper.h"
#include "Graphics/OpenGL/OpenGLWrapper.h"
#include "Graphics/OpenGL/Window.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
