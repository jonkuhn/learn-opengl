#include "Factory.h"
#include "Shader.h"

using namespace Graphics::OpenGL;

Factory::Factory(int winWidth, int winHeight, const std::string& title)
    : _glfw(),
      _window(&_glfw, winWidth, winHeight, title),
      _gl(&_window),
      _tileMapShaderProgram(&_gl),
      _unitQuadVertexArray(&_gl)
{

}

Graphics::ITileMap* Factory::CreateTileMap(
    IImage& tileMapImage,
    const glm::vec2& mapSizeInTiles,
    IImage& tileAtlasImage,
    const glm::vec2& atlasSizeInTiles)
{
    auto tileMapUniquePtr = std::make_unique<TileMap>(
        &_tileMapShaderProgram,
        &_unitQuadVertexArray,
        CreateTexture(Texture::Params(tileMapImage)
            .WrapModeS(Texture::WrapMode::ClampToBorder)
            .WrapModeT(Texture::WrapMode::ClampToBorder)
            .MinFilter(Texture::MinFilterMode::Nearest)
            .MagFilter(Texture::MagFilterMode::Nearest)),
        mapSizeInTiles,
        CreateTexture(Texture::Params(tileAtlasImage)
            .WrapModeS(Texture::WrapMode::ClampToBorder)
            .WrapModeT(Texture::WrapMode::ClampToBorder)
            .MinFilter(Texture::MinFilterMode::Nearest)
            .MagFilter(Texture::MagFilterMode::Nearest)),
        atlasSizeInTiles);
    auto* tileMap = tileMapUniquePtr.get();
    _tileMaps.push_back(std::move(tileMapUniquePtr));
    return tileMap;
}

Texture* Factory::CreateTexture(const Texture::Params &params)
{
    auto textureUniquePtr = std::make_unique<Texture>(&_gl, params);
    auto* texture = textureUniquePtr.get();
    _textures.push_back(std::move(textureUniquePtr));
    return texture;
}
