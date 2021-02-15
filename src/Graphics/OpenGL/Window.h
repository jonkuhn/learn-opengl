#pragma once
#include <functional>
#include <memory>
#include <string>

#include "IGlfwWrapper.h"
#include "IOpenGLWindow.h"

namespace Graphics::OpenGL
{
    class GlfwWindow : public IOpenGLWindow
    {
    public:
        GlfwWindow(IGlfwWrapper& glfw, int winWidth, int winHeight, const std::string& title);
        ~GlfwWindow();
        GlfwWindow(const GlfwWindow&) = delete;

        void Close();

        // Currently just a pass-thru to glfwGetKey
        int GetKey(int key);

        // Update returns true if the window can stay open and false
        // if it needs to close.
        bool Update();
    private:
        static GlfwWindow* s_singleInstance;
        static void FrameBufferSizeCallbackDispatch(GLFWwindow* window, int width, int height);
        void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);

        IGlfwWrapper& _glfw;

        typedef std::unique_ptr<GLFWwindow, std::function<void (GLFWwindow*)>> UniqueWindowHandle;
        UniqueWindowHandle _handle;
    };
}
