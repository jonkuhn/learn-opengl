#include "TileMapShaderProgram.h"

using namespace Graphics::OpenGL;

TileMapShaderProgram::TileMapShaderProgram(IShaderProgram* shaderProgram)
    : _shaderProgram(shaderProgram)
{

}

void TileMapShaderProgram::Use()
{
    _shaderProgram->Use();
}

void TileMapShaderProgram::ModelMatrix(const glm::mat4& model)
{
    _shaderProgram->SetUniform("model", model);
}

void TileMapShaderProgram::ViewMatrix(const glm::mat4& view)
{
    _shaderProgram->SetUniform("view", view);
}

void TileMapShaderProgram::ProjectionMatrix(const glm::mat4& projection)
{
    _shaderProgram->SetUniform("projection", projection);
}

void TileMapShaderProgram::Map(ITexture& mapTexture, const glm::vec2& mapSizeInTiles)
{
    const int mapTextureIndex = 0;
    mapTexture.Bind(mapTextureIndex);
    _shaderProgram->SetUniform("tileMap", mapTextureIndex);
    _shaderProgram->SetUniform("tileMapSizeInTiles", mapSizeInTiles);
}

void TileMapShaderProgram::Atlas(ITexture& atlasTexture, const glm::vec2& atlasSizeInTiles)
{
    const int atlasTextureIndex = 1;
    atlasTexture.Bind(atlasTextureIndex);
    _shaderProgram->SetUniform("tileAtlas", atlasTextureIndex);
    _shaderProgram->SetUniform("tileAtlasSizeInTiles", atlasSizeInTiles);
}
