#include "Factory.h"
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

    template <typename T>
    VertexArray<T> createVertexArrayForUnitQuad(IOpenGLWrapper *gl)
    {
        return VertexArray<T>(
            gl,
            typename VertexArray<T>::Params(
                std::vector<T>({
                    { 1.0f, 1.0f, 0.0f },  // top right
                    { 1.0f, 0.0f, 0.0f },  // bottom right
                    { 0.0f,  0.0f, 0.0f },  // bottom left
                    { 0.0f, 1.0f, 0.0f }   // top left 
                }))
                .AddAttribute(3)
                .TriangleElementIndices(
                    std::vector<GLuint>({
                        0, 1, 3,  // first Triangle
                        1, 2, 3   // second Triangle
                    }))
        );
    }

}

Factory::Factory(int winWidth, int winHeight, const std::string& title)
    : _glfw(),
      _window(&_glfw, winWidth, winHeight, title),
      _gl(&_window),
      _shaderProgramForTileMap(createShaderProgramForTileMap(&_gl)),
      _tileMapShaderProgram(&_shaderProgramForTileMap),
      _vertexArrayForUnitQuad(createVertexArrayForUnitQuad<SimpleVertex>(&_gl)),
      _unitQuadVertexArray(&_vertexArrayForUnitQuad)
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
