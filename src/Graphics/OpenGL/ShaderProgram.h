#pragma once

#include <initializer_list>
#include <string>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-volatile"
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#pragma clang diagnostic pop

#include "IShader.h"
#include "IOpenGLWrapper.h"

namespace Graphics::OpenGL
{
    class ShaderProgram
    {
    public:
        ShaderProgram(IOpenGLWrapper& gl, std::initializer_list<IShader*> shaders);
        ~ShaderProgram();
        ShaderProgram(const ShaderProgram&) = delete;

        void Use();
        void SetUniform(const std::string name, int value);
        void SetUniform(const std::string name, const glm::mat4& value);
        void SetUniform(const std::string name, const glm::vec3& value);

    private:
        IOpenGLWrapper& _gl;
        GLuint _handle;
    };
}