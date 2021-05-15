#pragma once

#include "../IFactory.h"
#include "TileMap.h"
#include "TileMapShaderProgram.h"

namespace Graphics::OpenGL
{
    class Factory : public IFactory
    {
    public:
        Factory(int winWidth, int winHeight, std::string& title);

        std::unique_ptr<ITileMap> CreateTileMap(
            IImage& tileMap,
            const glm::vec2& mapSizeInTiles,
            IImage& tileAtlas,
            const glm::vec2& atlasSizeInTiles) override;

    private:
        GlfwWrapper _glfw;
        GlfwWindow _window;
        OpenGLWrapper _gl;
        ShaderProgram _shaderProgramForTileMap;
        TileMapShaderProgram _tileMapShaderProgram;

        std::unique_ptr<TileMap> _tileMap;
        std::unique_ptr<TileMapShaderProgram> _tileMapShaderProgram;

        ITexture& CreateTexture(const IImage& image)
        {
        }
    };
}
