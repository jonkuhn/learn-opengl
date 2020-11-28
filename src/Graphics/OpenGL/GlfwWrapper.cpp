#include <string>
#include <sstream>

#include "GlfwWrapper.h"

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

namespace 
{
    void frameBufferSizeCallback(GLFWwindow* window, int width, int height)
    {
        // Not sure if it is worth dealing with possibility of more than one
        // window.  probably not.
        auto contextToRestore = glfwGetCurrentContext();

        // Make sure the correct context is current
        glfwMakeContextCurrent(window);

        // Make sure the viewport matches the new window dimensions
        glViewport(0, 0, width, height);
        
        glfwMakeContextCurrent(contextToRestore);
    }
}

GLFWwindow* Graphics::OpenGL::InitializeGlfwAndGlad(IGlfwWrapper& glfw, int winWidth, int winHeight)
{
    // TODO:
    // - Create a window class (in separate files)
    // - Create a GLFW library wrapper (to make window class unit testable)
    // - Maybe Create a GLAD library wrapper (the GLAD loader is likely called by the window class too)
    // - Then, likey this OpenGLWrapper (maybe renamed with OpenGL in its name) depends on a window
    if (glfw.Init() != GLFW_TRUE)
    {
        throw GlfwException(glfw, "Failed to initialize GLFW.");
    }

    glfw.WindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfw.WindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfw.WindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfw.WindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    auto window = glfw.CreateWindow(winWidth, winHeight, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        glfw.Terminate();
        throw GlfwException(glfw, "Failed to create GLFW window.");
    }
    glfw.MakeContextCurrent(window);
    glfw.SetFramebufferSizeCallback(window, frameBufferSizeCallback);

    if (!glfw.LoadGLLoader())
    {
        throw std::runtime_error("Failed to initialize GLAD");
    } 

    return window;
}