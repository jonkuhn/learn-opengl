#pragma once

#include <string>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-volatile"
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#pragma clang diagnostic pop

namespace Graphics::OpenGL
{
    class IShaderProgram
    {
    public:
        void Use();
        void SetUniform(const std::string &name, int value);
        void SetUniform(const std::string &name, const glm::mat4& value);
        void SetUniform(const std::string &name, const glm::vec3& value);
        void SetUniform(const std::string &name, const glm::vec2& value);

    protected:
        // This interface is not intended to expose ownership of the
        // concrete object implementing it.  Therefore, do not allow
        // deletion via interface pointers.
        ~IShaderProgram() = default;
    };
}