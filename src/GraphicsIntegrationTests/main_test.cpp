#include <gtest/gtest.h>

// TODO: remove this
#include "Graphics/OpenGL/LibraryWrapper.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  // TODO: remove this
  InitializeGlfwAndGlad(800, 600);

  return RUN_ALL_TESTS();
}