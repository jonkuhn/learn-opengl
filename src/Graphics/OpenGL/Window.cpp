#include "Window.h"
#include "GlfwException.h"

using namespace Graphics::OpenGL;

Window* Window::s_singleInstance = nullptr;

Window::Window(IGlfwWrapper& glfw, int winWidth, int winHeight, const std::string& title)
    : _glfw(glfw)
{
    // Many of the GLFW calls below must only be called from the main
    // thread anyway, so there is not much sense in making this check
    // thread safe.
    if (s_singleInstance != nullptr)
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

    _handle = _glfw.CreateWindow(winWidth, winHeight, title.c_str(), nullptr, nullptr);
    if (_handle == nullptr)
    {
        throw GlfwException(glfw, "Failed to create GLFW window.");
    }
    _glfw.MakeContextCurrent(_handle);
    _glfw.SetFramebufferSizeCallback(_handle, FrameBufferSizeCallbackDispatch);

    if (!_glfw.LoadGl())
    {
        throw std::runtime_error("Failed to initialize OpenGL using GLFW and GLAD");
    } 
    s_singleInstance = this;
}

Window::~Window()
{
    _glfw.DestroyWindow(_handle);
    s_singleInstance = nullptr;
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

void Window::FrameBufferSizeCallbackDispatch(GLFWwindow* window, int width, int height)
{
    // For now keep dispatch simple since we are only allowing
    // one instance of Window at a time.  If we ever want multiple
    // instances we should instead use glfwSetWindowUserPointer/glfwGetWindowUserPointer
    // but that will also make it so this static function depends on GLFW
    // which we wanted to be able to replace for testing.
    s_singleInstance->FrameBufferSizeCallback(window, width, height);
}

void Window::FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    // Make sure the right context is current, even though
    // currently this class is limited to one instance at a
    // time. (see comment in constructor)
    _glfw.MakeContextCurrent(window);

    // Make sure the viewport matches the new window dimensions
    _glfw.SetGlViewport(0, 0, width, height);
}
