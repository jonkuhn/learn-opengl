#pragma once

#include "../IFactory.h"
#include "TileMap.h"

namespace Graphics::OpenGL
{
    class Factory : public IFactory
    {
    public:
        std::unique_ptr<ITileMap> CreateTileMap(
            IImage& tileMap,
            const glm::vec2& mapSizeInTiles,
            IImage &tileAtlas,
            const glm::vec2& atlasSizeInTiles) override
        {
            return std::make_unique<TileMap>(
                CreateTileMapShaderProgram(),
                CreateTexture(tileMap),
                mapSizeInTiles,
                CreateTexture(tileAtlas),
                atlasSizeInTiles);
        }

    private:
        // If this is the approach I take, this needs to hold onto
        // the TileMapShaderProgram in a member variable and just
        // return a reference here.
        ITileMapShaderProgram& CreateTileMapShaderProgram()
        {
            const char *vertexShaderSource = R"##RAW##(
            #version 330 core
            layout (location = 0) in vec3 vertex;

            out vec2 tileMapLocation;

            uniform mat4 model;
            uniform mat4 view;
            uniform mat4 projection;

            void main()
            {
                tileMapLocation = vertex.xy;
                gl_Position = projection * view * model * vec4(vertex.xy, 0.0, 1.0);
            }
            )##RAW##";

            const char *fragmentShaderSource = R"##RAW##(
            #version 330 core
            uniform vec2 tileMapSizeInTiles;
            uniform sampler2D tileMap;
            uniform sampler2D tileAtlas;
            uniform vec2 tileAtlasSizeInTiles;

            in vec2 tileMapLocation;

            out vec4 FragColor;

            void main()
            {
                vec2 tileAtlasLocation = texture(tileMap, tileMapLocation / tileMapSizeInTiles).xy * 255;
                FragColor = texture(tileAtlas, (tileAtlasLocation + fract(tileMapLocation)) / tileAtlasSizeInTiles);
            }
            )##RAW##";
            Shader vertexShader(gl, Shader::Type::Vertex, vertexShaderSource);
            Shader fragmentShader(gl, Shader::Type::Fragment, fragmentShaderSource);
            ShaderProgram shaderProgram(gl, {&vertexShader, &fragmentShader});
            TileMapShaderProgram tileMapShaderProgram(shaderProgram);
        }

        ITexture& CreateTexture(const IImage& image)
        {
        }
    };
}
