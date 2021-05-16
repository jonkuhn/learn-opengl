#include "TileMap.h"

using namespace Graphics::OpenGL;

TileMap::TileMap(
    ITileMapShaderProgram* tileMapShaderProgram,
    IUnitQuadVertexArray* unitQuadVertexArray,
    ITexture* mapTexture,
    glm::vec2 mapSizeInTiles,
    ITexture* atlasTexture,
    glm::vec2 atlasSizeInTiles)
    : _tileMapShaderProgram(tileMapShaderProgram),
      _unitQuadVertexArray(unitQuadVertexArray),
      _mapTexture(mapTexture),
      _mapSizeInTiles(std::move(mapSizeInTiles)),
      _atlasTexture(atlasTexture),
      _atlasSizeInTiles(std::move(atlasSizeInTiles))
{

}

void TileMap::Draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection)
{
    _tileMapShaderProgram->Use();
    _tileMapShaderProgram->Map(*_mapTexture, _mapSizeInTiles);
    _tileMapShaderProgram->Atlas(*_atlasTexture, _atlasSizeInTiles);
    _tileMapShaderProgram->ModelMatrix(model);
    _tileMapShaderProgram->ViewMatrix(view);
    _tileMapShaderProgram->ProjectionMatrix(projection);
    _unitQuadVertexArray->Draw();
}
