#pragma once

#include <stdexcept>
#include <string>

#include "IGlfwWrapper.h"

namespace Graphics::OpenGL
{
    class GlfwException final : public std::runtime_error
    {
    public:
        GlfwException(IGlfwWrapper& glfw, const std::string& prefix);
    };
}
