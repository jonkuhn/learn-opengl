#pragma once
#include "./ILibraryWrapper.h"

#include <mutex>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace
{
    std::string GetGlfwExceptionMessage(const std::string& prefix)
    {
        const char* description = nullptr;
        int code = glfwGetError(&description);
        std::stringstream ss;
        ss << prefix
            << " Code: " << code
            << " Description: " << std::string(description);

        return ss.str();
    }
}

class GlfwException : public std::runtime_error
{
public:
    GlfwException(const std::string& prefix)
        : std::runtime_error(GetGlfwExceptionMessage(prefix))
    {

    }
};

// TODO: make window class
GLFWwindow* InitializeGlfwAndGlad(int winWidth, int winHeight);

namespace Graphics::OpenGL
{
    class LibraryWrapper : public ILibraryWrapper
    {
    public:
        GLuint CreateShader(GLenum shaderType) override
        {
            return glCreateShader(shaderType);
        };

        void ShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length) override
        {
            glShaderSource(shader, count, string, length);
        };

        void CompileShader(GLuint shader) override
        {
            glCompileShader(shader);
        };

        void GetShaderiv(GLuint shader, GLenum pname, GLint* params) override
        {
            glGetShaderiv(shader, pname, params);
        }

        void GetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog) override
        {
            glGetShaderInfoLog(shader, maxLength, length, infoLog);
        }

        void DeleteShader(GLuint shader) override
        {
            glDeleteShader(shader);
        }
    };
}