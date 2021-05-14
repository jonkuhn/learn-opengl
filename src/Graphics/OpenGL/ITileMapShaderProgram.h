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
        virtual void Use();
        virtual void ModelMatrix(const glm::mat4& model);
        virtual void ViewMatrix(const glm::mat4& view);
        virtual void ProjectionMatrix(const glm::mat4& projection);
        virtual void Map(int textureIndex, const glm::vec2& mapSizeInTiles);
        virtual void Atlas(int textureIndex, const glm::vec2& atlasSizeInTiles);

    protected:
        // This interface is not intended to expose ownership of the
        // concrete object implementing it.  Therefore, do not allow
        // deletion via interface pointers.
        ~ITileMapShaderProgram() = default;
    };
}