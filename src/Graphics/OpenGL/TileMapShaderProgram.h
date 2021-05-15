#pragma once
#include <memory>

#include "ShaderProgram.h"
#include "ITileMapShaderProgram.h"

namespace Graphics::OpenGL
{
    class TileMapShaderProgram : public ITileMapShaderProgram
    {
    public:
        TileMapShaderProgram(IShaderProgram* shaderProgram);

        TileMapShaderProgram(TileMapShaderProgram&& other) = default;
        TileMapShaderProgram& operator=(TileMapShaderProgram&& other) = default;

        TileMapShaderProgram(const TileMapShaderProgram& other) = delete;
        TileMapShaderProgram& operator=(const TileMapShaderProgram& other) = delete;

        void Use() override;
        void ModelMatrix(const glm::mat4& model) override;
        void ViewMatrix(const glm::mat4& view) override;
        void ProjectionMatrix(const glm::mat4& projection) override;
        void Map(int textureIndex, const glm::vec2  &mapSizeInTiles) override;
        void Atlas(int textureIndex, const glm::vec2& atlasSizeInTiles) override;

    private:
        IShaderProgram* _shaderProgram;
    };
}