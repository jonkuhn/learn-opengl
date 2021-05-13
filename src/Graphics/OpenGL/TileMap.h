#pragma once

#include "../ITileMap.h"

#include "ITexture.h"
#include "ITileMapShaderProgram.h"

namespace Graphics::OpenGL
{
    class TileMap : public ITileMap
    {
    public:
        TileMap(
            ITileMapShaderProgram* tileMapShaderProgram,
            ITexture* mapTexture,
            const glm::vec2& mapSizeInTiles,
            ITexture* atlasTexture,
            const glm::vec2& atlasSizeInTiles);

        TileMap(TileMap&& other) = default;
        TileMap& operator=(TileMap&& other) = default;

        TileMap(const TileMap& other) = delete;
        TileMap& operator=(const TileMap& other) = delete;
        
        void Draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);
    };
}