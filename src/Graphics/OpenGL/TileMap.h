#pragma once

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-volatile"
#include <glm/vec3.hpp>
#pragma clang diagnostic pop

#include "../ITileMap.h"

#include "ITexture.h"
#include "ITileMapShaderProgram.h"
#include "IUnitQuadVertexArray.h"

namespace Graphics::OpenGL
{
    class TileMap final : public ITileMap
    {
    public:
        TileMap(
            ITileMapShaderProgram* tileMapShaderProgram,
            IUnitQuadVertexArray* unitQuadVertexArray,
            ITexture* mapTexture,
            glm::vec2 mapSizeInTiles,
            ITexture* atlasTexture,
            glm::vec2 atlasSizeInTiles);

        TileMap(TileMap&& other) = default;
        TileMap& operator=(TileMap&& other) = default;

        TileMap(const TileMap& other) = delete;
        TileMap& operator=(const TileMap& other) = delete;
        
        void Draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);

    private:
        ITileMapShaderProgram* _tileMapShaderProgram;
        IUnitQuadVertexArray* _unitQuadVertexArray;
        ITexture* _mapTexture;
        glm::vec2 _mapSizeInTiles;
        ITexture* _atlasTexture;
        glm::vec2 _atlasSizeInTiles;
    };
}