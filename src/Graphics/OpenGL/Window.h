#pragma once
#include "IGlfwWrapper.h"

namespace Graphics::OpenGL
{
    // TODO: make window class
    GLFWwindow* InitializeGlfwAndGlad(IGlfwWrapper& glfw, int winWidth, int winHeight);
}