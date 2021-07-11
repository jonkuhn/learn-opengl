#pragma once

#include <string>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-volatile"
#include <glm/glm.hpp>
#pragma clang diagnostic pop

namespace Graphics::OpenGL
{
    class IShaderProgram
    {
    public:
        virtual void Use() = 0;
        virtual void SetUniform(const std::string &name, int value) = 0;
        virtual void SetUniform(const std::string &name, const glm::mat4& value) = 0;
        virtual void SetUniform(const std::string &name, const glm::vec3& value) = 0;
        virtual void SetUniform(const std::string &name, const glm::vec2& value) = 0;

        // This interface allows for deletion so that ownership can be
        // held via this interface.  This enables unit testing of use
        // cases such as TileMapShaderProgram
        virtual ~IShaderProgram() = default;
    };
}
