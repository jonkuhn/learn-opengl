#include "Factory.h"

using namespace Graphics::OpenGL;

namespace
{
    ShaderProgram createShaderProgramForTileMap()
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
        Shader vertexShader(&_gl, Shader::Type::Vertex, vertexShaderSource);

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
        Shader fragmentShader(&_gl, Shader::Type::Fragment, fragmentShaderSource);

        // Note that the vertex and fragment shader instances can be destroyed
        // after the shader program has been constructed.

        ShaderProgram shaderProgram(&_gl, {&vertexShader, &fragmentShader});
        return std::move(shaderProgram);
    }
}

Factory::Factory(int winWidth, int winHeight, std::string& title)
    : _glfw(),
      _window(&_glfw, winWidth, winHeight, title),
      _gl(&_window),
      _shaderProgramForTileMap(createShaderProgramForTileMap()),
      _tileMapShaderProgram(_shaderProgramForTileMap)
{

}

ITileMap* Factory::CreateTileMap(
    IImage& tileMap,
    const glm::vec2& mapSizeInTiles,
    IImage& tileAtlas,
    const glm::vec2& atlasSizeInTiles) override;
{
    return std::make_unique<TileMap>(
        _tileMapShaderProgram,
        CreateTexture(tileMap),
        mapSizeInTiles,
        CreateTexture(tileAtlas),
        atlasSizeInTiles);
}
