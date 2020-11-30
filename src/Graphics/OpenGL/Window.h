#pragma once
#include <string>

#include "IGlfwWrapper.h"

namespace Graphics::OpenGL
{
    class Window
    {
    public:
        Window(IGlfwWrapper& glfw, int winWidth, int winHeight, const std::string& title);
        ~Window();
        Window(const Window&) = delete;

        void Close();

        // Currently just a pass-thru to glfwGetKey
        int GetKey(int key);

        // Update returns true if the window can stay open and false
        // if it needs to close.
        bool Update();
    private:
        static bool _instanceExists;

        IGlfwWrapper& _glfw;
        GLFWwindow* _handle;
    };
}