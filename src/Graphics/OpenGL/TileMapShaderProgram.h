#pragma once

#include "IShaderProgram.h"
#include "ITileMapShaderProgram.h"

namespace Graphics::OpenGL
{
    class TileMapShaderProgram : public ITileMapShaderProgram
    {
    public:
        TileMapShaderProgram(IShaderProgram& shaderProgram);
        void Use() override;
        void ModelMatrix(const glm::mat4& model) override;
        void ViewMatrix(const glm::mat4& view) override;
        void ProjectionMatrix(const glm::mat4& projection) override;
        void Map(int textureIndex, const glm::vec2  &mapSizeInTiles) override;
        void Atlas(int textureIndex, const glm::vec2& atlasSizeInTiles) override;

    private:
        IShaderProgram &_shaderProgram;
    };
}