#pragma once

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-volatile"
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#pragma clang diagnostic pop

namespace Graphics::OpenGL
{
    class ITileMapShaderProgram
    {
    public:
        virtual void Use() = 0;
        virtual void ModelMatrix(const glm::mat4& model) = 0;
        virtual void ViewMatrix(const glm::mat4& view) = 0;
        virtual void ProjectionMatrix(const glm::mat4& projection) = 0;
        virtual void Map(ITexture& mapTexture, const glm::vec2  &mapSizeInTiles) = 0;
        virtual void Atlas(ITexture& mapTexture, const glm::vec2& atlasSizeInTiles) = 0;

    protected:
        // This interface is not intended to expose ownership of the
        // concrete object implementing it.  Therefore, do not allow
        // deletion via interface pointers.
        ~ITileMapShaderProgram() = default;
    };
}