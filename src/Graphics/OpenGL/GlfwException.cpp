#include <string>
#include <sstream>

#include "GlfwException.h"

using namespace Graphics::OpenGL;

namespace
{
    std::string GetGlfwExceptionMessage(IGlfwWrapper& glfw, const std::string& prefix)
    {
        const char* description = nullptr;
        int code = glfw.GetError(&description);
        std::stringstream ss;
        ss << prefix
            << " Code: " << code
            << " Description: " << std::string(description);

        return ss.str();
    }
}

GlfwException::GlfwException(IGlfwWrapper& glfw, const std::string& prefix)
    : std::runtime_error(GetGlfwExceptionMessage(glfw, prefix))
{

}