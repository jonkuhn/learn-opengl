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

GlfwWindow& Factory::GetWindow()
{
    return _window;
}


Graphics::ITileMap* Factory::CreateTileMap(
    TextureHandle tileMapTexture,
    const glm::vec2& mapSizeInTiles,
    TextureHandle tileAtlasTexture,
    const glm::vec2& atlasSizeInTiles)
{
    auto tileMapUniquePtr = std::make_unique<TileMap>(
        &_tileMapShaderProgram,
        &_unitQuadVertexArray,
        static_cast<ITexture*>(tileMapTexture.p),
        mapSizeInTiles,
        static_cast<ITexture*>(tileAtlasTexture.p),
        atlasSizeInTiles);
    auto* tileMap = tileMapUniquePtr.get();
    _tileMaps.push_back(std::move(tileMapUniquePtr));
    return tileMap;
}

Graphics::TextureHandle Factory::CreateTexture(IImage& image)
{
    auto textureUniquePtr = std::make_unique<Texture>(
        &_gl,
        Texture::Params(image)
            .WrapModeS(Texture::WrapMode::ClampToBorder)
            .WrapModeT(Texture::WrapMode::ClampToBorder)
            .MinFilter(Texture::MinFilterMode::Nearest)
            .MagFilter(Texture::MagFilterMode::Nearest));
    TextureHandle handle(textureUniquePtr.get());
    _textures.push_back(std::move(textureUniquePtr));
    return handle;
}
