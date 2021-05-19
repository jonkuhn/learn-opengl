#pragma once

#include "../IFactory.h"
#include "GlfwWrapper.h"
#include "OpenGLWrapper.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "TileMap.h"
#include "TileMapShaderProgram.h"
#include "UnitQuadVertexArray.h"
#include "VertexArray.h"
#include "Window.h"

namespace Graphics::OpenGL
{
    class Factory : public IFactory
    {
    public:
        Factory(int winWidth, int winHeight, const std::string& title);

        GlfwWindow& GetWindow()
        {
            return _window;
        }

        Graphics::ITileMap* CreateTileMap(
            IImage& tileMap,
            const glm::vec2& mapSizeInTiles,
            IImage& tileAtlas,
            const glm::vec2& atlasSizeInTiles) override;

    private:
        struct SimpleVertex
        {
            float x;
            float y;
            float z;
        };

        GlfwWrapper _glfw;
        GlfwWindow _window;
        OpenGLWrapper _gl;
        ShaderProgram _shaderProgramForTileMap;
        TileMapShaderProgram _tileMapShaderProgram;
        VertexArray<SimpleVertex> _vertexArrayForUnitQuad;
        UnitQuadVertexArray _unitQuadVertexArray;

        std::vector<std::unique_ptr<Texture>> _textures;
        std::vector<std::unique_ptr<TileMap>> _tileMaps;

        Texture* CreateTexture(const Texture::Params &params);
    };
}
