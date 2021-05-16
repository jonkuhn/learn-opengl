#include "TileMapShaderProgram.h"

#include "Shader.h"

using namespace Graphics::OpenGL;

namespace
{
    ShaderProgram createShaderProgramForTileMap(IOpenGLWrapper* gl)
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
            vec4 tileMapLocationVec4 = (model * vec4(vertex.xy, 0.0, 1.0));
            tileMapLocation = tileMapLocationVec4.xy;
            gl_Position = projection * view * tileMapLocationVec4;
        }
        )##RAW##";
        Shader vertexShader(gl, Shader::Type::Vertex, vertexShaderSource);

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
        Shader fragmentShader(gl, Shader::Type::Fragment, fragmentShaderSource);

        // Note that the vertex and fragment shader instances can be destroyed
        // after the shader program has been constructed.

        ShaderProgram shaderProgram(gl, {&vertexShader, &fragmentShader});
        return shaderProgram;
    }
}

TileMapShaderProgram::TileMapShaderProgram(IOpenGLWrapper* gl)
    : _shaderProgram(createShaderProgramForTileMap(gl))
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

void TileMapShaderProgram::Map(ITexture& mapTexture, const glm::vec2& mapSizeInTiles)
{
    const int mapTextureIndex = 0;
    mapTexture.Bind(mapTextureIndex);
    _shaderProgram.SetUniform("tileMap", mapTextureIndex);
    _shaderProgram.SetUniform("tileMapSizeInTiles", mapSizeInTiles);
}

void TileMapShaderProgram::Atlas(ITexture& atlasTexture, const glm::vec2& atlasSizeInTiles)
{
    const int atlasTextureIndex = 1;
    atlasTexture.Bind(atlasTextureIndex);
    _shaderProgram.SetUniform("tileAtlas", atlasTextureIndex);
    _shaderProgram.SetUniform("tileAtlasSizeInTiles", atlasSizeInTiles);
}
