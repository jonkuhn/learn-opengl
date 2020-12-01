#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Graphics::OpenGL
{
    class IGlfwWrapper
    {
    public:
        virtual void WindowHint(int hint, int value) = 0;
        virtual GLFWwindow* CreateWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share) = 0;
        virtual void DestroyWindow(GLFWwindow* window) = 0;
        virtual void MakeContextCurrent(GLFWwindow* window) = 0;
        virtual GLFWwindow* GetCurrentContext() = 0;
        virtual GLFWframebuffersizefun SetFramebufferSizeCallback(GLFWwindow* window, GLFWframebuffersizefun callback) = 0;
        virtual int GetError(const char** description) = 0;
        virtual void SwapBuffers(GLFWwindow* window) = 0;
        virtual void PollEvents() = 0;
        virtual int GetKey(GLFWwindow* window, int key) = 0;
        virtual void SetWindowShouldClose(GLFWwindow* window, int value) = 0;
        virtual int WindowShouldClose(GLFWwindow* window) = 0;
        virtual int LoadGl() = 0;

        // Note: this is here instead of in IOpenGLWrapper because the
        // Window class depends on it and having it here keeps things
        // simpler.
        virtual void SetGlViewport(GLint x, GLint y, GLsizei width, GLsizei height) = 0;
    };
}
