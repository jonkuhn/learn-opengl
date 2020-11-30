
#include "Window.h"

#include "GlfwException.h"

using namespace Graphics::OpenGL;

namespace 
{
    void frameBufferSizeCallback(GLFWwindow* window, int width, int height)
    {
        // Make sure the right context is current, even though
        // currently this class is limited to one instance at a
        // time. (see comment in constructor)
        glfwMakeContextCurrent(window);

        // Make sure the viewport matches the new window dimensions
        glViewport(0, 0, width, height);
    }
}


bool Window::_instanceExists = false;

Window::Window(IGlfwWrapper& glfw, int winWidth, int winHeight, const std::string& title)
    : _glfw(glfw)
{
    // Many of the GLFW calls below must only be called from the main
    // thread anyway, so there is not much sense in making this check
    // thread safe.
    if (_instanceExists == true)
    {
        // To allow for multiple windows we would need to be able to
        // make sure _glfw.MakeContextCurrent is called for the appropriate
        // window before making OpenGL calls for that window.
        throw std::logic_error(
            "To simplify context management, the Window class currently "
            "only supports one instance at a time.");
    }

    _glfw.WindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    _glfw.WindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    _glfw.WindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    _glfw.WindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    _handle = _glfw.CreateWindow(winWidth, winHeight, title.c_str(), NULL, NULL);
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
    _instanceExists = true;
}

Window::~Window()
{
    _glfw.DestroyWindow(_handle);
    _instanceExists = false;
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
    return !_glfw.WindowShouldClose(_handle);
}