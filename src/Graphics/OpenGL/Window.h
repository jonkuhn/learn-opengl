#pragma once
#include "IGlfwWrapper.h"

namespace Graphics::OpenGL
{
    class Window
    {
    public:
        Window(IGlfwWrapper& glfw, int winWidth, int winHeight);
        ~Window();
        Window(const Window&) = delete;

        void Close();

        // Currently just a pass-thru to glfwGetKey
        int GetKey(int key);

        // Update returns true if the window can stay open and false
        // if it needs to close.
        bool Update();
    private:
        IGlfwWrapper& _glfw;
        GLFWwindow* _handle;
    };
}