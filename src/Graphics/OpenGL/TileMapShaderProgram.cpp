#include "TileMapShaderProgram.h"

using namespace Graphics::OpenGL;

TileMapShaderProgram::TileMapShaderProgram(IShaderProgram &shaderProgram)
    : _shaderProgram(shaderProgram)
{

}

void TileMapShaderProgram::Use()
{
    _shaderProgram.Use();
}

void TileMapShaderProgram::ModelMatrix(const glm::mat4& model)
{
    _shaderProgram.SetUniform("model", model);
}

void TileMapShaderProgram::ViewMatrix(const glm::mat4& view)
{
    _shaderProgram.SetUniform("view", view);
}

void TileMapShaderProgram::ProjectionMatrix(const glm::mat4& projection)
{
    _shaderProgram.SetUniform("projection", projection);
}

void TileMapShaderProgram::Map(int textureIndex, const glm::vec2& mapSizeInTiles)
{
    _shaderProgram.SetUniform("tileMap", textureIndex);
    _shaderProgram.SetUniform("tileMapSizeInTiles", mapSizeInTiles);
}

void TileMapShaderProgram::Atlas(int textureIndex, const glm::vec2& atlasSizeInTiles)
{
    _shaderProgram.SetUniform("tileAtlas", textureIndex);
    _shaderProgram.SetUniform("tileAtlasSizeInTiles", atlasSizeInTiles);
}

