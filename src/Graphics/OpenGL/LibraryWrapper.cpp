#include "LibraryWrapper.h"

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

GLFWwindow* InitializeGlfwAndGlad(int winWidth, int winHeight)
{
    // TODO:
    // - Create a window class (in separate files)
    // - Create a GLFW library wrapper (to make window class unit testable)
    // - Maybe Create a GLAD library wrapper (the GLAD loader is likely called by the window class too)
    // - Then, likey this LibraryWrapper (maybe renamed with OpenGL in its name) depends on a window
    if (glfwInit() != GLFW_TRUE)
    {
        throw GlfwException("Failed to initialize GLFW.");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    auto window = glfwCreateWindow(winWidth, winHeight, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        glfwTerminate();
        throw GlfwException("Failed to create GLFW window.");
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD");
    } 

    return window;
}