
#include "Window.h"

#include "GlfwException.h"

using namespace Graphics::OpenGL;

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

Window::Window(IGlfwWrapper& glfw, int winWidth, int winHeight)
    : _glfw(glfw)
{
    _glfw.WindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    _glfw.WindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    _glfw.WindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    _glfw.WindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    _handle = _glfw.CreateWindow(winWidth, winHeight, "LearnOpenGL", NULL, NULL);
    if (_handle == NULL)
    {
        throw GlfwException(glfw, "Failed to create GLFW window.");
    }
    _glfw.MakeContextCurrent(_handle);
    _glfw.SetFramebufferSizeCallback(_handle, frameBufferSizeCallback);

    if (!_glfw.LoadGLLoader())
    {
        throw std::runtime_error("Failed to initialize OpenGL using GLFW and GLAD");
    } 
}

Window::~Window()
{
    _glfw.DestroyWindow(_handle);
}

void Window::Close()
{
    _glfw.SetWindowShouldClose(_handle, true);
}

int Window::GetKey(int key)
{
    return _glfw.GetKey(_handle, key);
}

bool Window::Update()
{
    _glfw.SwapBuffers(_handle);
    _glfw.PollEvents();
    return _glfw.WindowShouldClose(_handle);
}