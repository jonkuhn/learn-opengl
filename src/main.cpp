#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#include <string>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-volatile"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#pragma clang diagnostic pop

#include "Graphics/LibPngWrapper.h"
#include "Graphics/OpenGL/GlfwWrapper.h"
#include "Graphics/OpenGL/OpenGLWrapper.h"
#include "Graphics/OpenGL/Shader.h"
#include "Graphics/OpenGL/ShaderProgram.h"
#include "Graphics/OpenGL/Texture.h"
#include "Graphics/OpenGL/VertexArray.h"
#include "Graphics/OpenGL/Window.h"
#include "Graphics/PngImage.h"

using namespace Graphics;
using namespace Graphics::OpenGL;

// settings
constexpr unsigned int SCR_WIDTH = 800;
constexpr unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = R"##RAW##(
#version 330 core
layout (location = 0) in vec3 vertex;

out vec2 tileMapLocation;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    tileMapLocation = vertex.xy;
    gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
}
)##RAW##";

const char *fragmentShaderSource = R"##RAW##(
#version 330 core
uniform vec2 tileSizeInPixels;
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

void processInput(GlfwWindow& window)
{
    if(window.GetKey(GLFW_KEY_ESCAPE) == GLFW_PRESS)
        window.Close();
}

struct Vertex
{
    float x;
    float y;
    float z;
};

class RandomTileMap : public IImage
{
public:
    RandomTileMap(int width, int height)
        : _width(width),
          _height(height),
          _data(4 * _width * _height)
    {
        for(int x = 0; x < _width; x++)
        {
            for(int y = 0; y < _height; y++)
            {
                _data[y * _width * 4 + x * 4 + 0] = std::rand() % 2;
                _data[y * _width * 4 + x * 4 + 1] = std::rand() % 2;
                _data[y * _width * 4 + x * 4 + 2] = 0;
                _data[y * _width * 4 + x * 4 + 3] = 0;
            }
        }
    }

    const uint8_t* Data() const
    {
        return _data.data();
    }

    int Width() const
    {
        return _width;
    }

    int Height() const
    {
        return _height;
    }

    PixelFormat Format() const
    {
        return IImage::PixelFormat::RGBA;
    }

private:
    int _width;
    int _height;
    std::vector<uint8_t> _data;
};

int main()
{
    GlfwWrapper glfw;
    GlfwWindow window(glfw, SCR_WIDTH, SCR_HEIGHT, "Learn OpenGL");
    OpenGLWrapper gl(window);
    LibPngWrapper libpng;

    Shader vertexShader(&gl, Shader::Type::Vertex, vertexShaderSource);
    Shader fragmentShader(&gl, Shader::Type::Fragment, fragmentShaderSource);
    ShaderProgram shaderProgram(&gl, {&vertexShader, &fragmentShader});

    //VertexArray<Vertex> vertexArray(
    //    gl,
    //    VertexArray<Vertex>::Params(
    //        std::vector<Vertex>({
    //            { 0.5f,  0.5f, 0.0f },  // top right
    //            { 0.5f, -0.5f, 0.0f },  // bottom right
    //            {-0.5f, -0.5f, 0.0f },  // bottom left
    //            {-0.5f,  0.5f, 0.0f }   // top left 
    //        }))
    //        .AddAttribute(3)
    //        .TriangleElementIndices(
    //            std::vector<GLuint>({
    //                0, 1, 3,  // first Triangle
    //                1, 2, 3   // second Triangle
    //            }))
    //    );


    // Draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Want:
    // - World to be 1000 tiles by 1000 tiles
    // - View to be 10 tiles by 10 tiles
    // - Each tile to be 64 by 64 pixels
    // - So world is 64,000 by 64,000
    // - So view is 640 by 640
    const float TILE_WIDTH_IN_PIXELS = 64;
    const float TILE_HEIGHT_IN_PIXELS = 64;
    const float WORLD_WIDTH_IN_TILES = 100;
    const float WORLD_HEIGHT_IN_TILES = 100; 
    const float TILE_SET_WIDTH_IN_TILES = 2;
    const float TILE_SET_HEIGHT_IN_TILES = 2;
    //const float WORLD_WIDTH = WORLD_WIDTH_IN_TILES * TILE_WIDTH_IN_PIXELS;
    //const float WORLD_HEIGHT = WORLD_HEIGHT_IN_TILES * TILE_HEIGHT_IN_PIXELS;
    const float VIEW_WIDTH_IN_TILES = 10;
    const float VIEW_HEIGHT_IN_TILES = 10;

    VertexArray<Vertex> vertexArray(
        &gl,
        VertexArray<Vertex>::Params(
            std::vector<Vertex>({
                { WORLD_WIDTH_IN_TILES, WORLD_HEIGHT_IN_TILES, 0.0f },  // top right
                { WORLD_WIDTH_IN_TILES, 0.0f, 0.0f },  // bottom right
                { 0.0f,  0.0f, 0.0f },  // bottom left
                { 0.0f, WORLD_HEIGHT_IN_TILES, 0.0f }   // top left 
            }))
            .AddAttribute(3)
            .TriangleElementIndices(
                std::vector<GLuint>({
                    0, 1, 3,  // first Triangle
                    1, 2, 3   // second Triangle
                }))
        );


    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));  
    shaderProgram.SetUniform("model", model);

    // With orthographic projection, I don't think a view matrix makes a lot of sense
    // because the visible area can be set directly in the orthographic projection
    // matrix
    //glm::mat4 view = glm::mat4(1.0f);
    //view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f)); 

    glEnable(GL_BLEND);

    RandomTileMap randomTileMap(WORLD_WIDTH_IN_TILES, WORLD_HEIGHT_IN_TILES);
    Texture tileMap(gl, Texture::Params(randomTileMap)
        .WrapModeS(Texture::WrapMode::ClampToBorder)
        .WrapModeT(Texture::WrapMode::ClampToBorder)
        .MinFilter(Texture::MinFilterMode::Nearest)
        .MagFilter(Texture::MagFilterMode::Nearest));

    PngImage tileAtlasImage(libpng, "/Users/jkuhn/scribbletiles.png");
    Texture tileAtlas(gl, Texture::Params(tileAtlasImage)
        .WrapModeS(Texture::WrapMode::ClampToBorder)
        .WrapModeT(Texture::WrapMode::ClampToBorder)
        .MinFilter(Texture::MinFilterMode::Nearest)
        .MagFilter(Texture::MagFilterMode::Nearest));

    tileMap.Bind(0);
    shaderProgram.SetUniform("tileMap", 0);
    tileAtlas.Bind(1);
    shaderProgram.SetUniform("tileAtlas", 1);

    //glm::mat4 projection = glm::ortho(0.0f, 10.0f, 0.0f, 10.0f, -1.0f, 1.0f);
    //shaderProgram.SetUniform("projection", projection);

    glm::vec2 tileSizeInPixels = glm::vec2(TILE_WIDTH_IN_PIXELS, TILE_HEIGHT_IN_PIXELS);
    shaderProgram.SetUniform("tileSizeInPixels", tileSizeInPixels);

    glm::vec2 tileAtlasSizeInTiles = glm::vec2(TILE_SET_WIDTH_IN_TILES, TILE_SET_HEIGHT_IN_TILES);
    shaderProgram.SetUniform("tileAtlasSizeInTiles", tileAtlasSizeInTiles);

    glm::vec2 tileMapSizeInTiles = glm::vec2(WORLD_WIDTH_IN_TILES, WORLD_HEIGHT_IN_TILES);
    shaderProgram.SetUniform("tileMapSizeInTiles", tileMapSizeInTiles);

    const float MOVE_SPEED = 5.0f;

    auto cameraX = 0.0f;
    auto cameraY = 0.0f;
    auto cameraDX = 0.0f;
    auto cameraDY = 0.0f;

    double previousTime = glfwGetTime();

    while (window.Update())
    {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.Use();
        
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - previousTime;
        previousTime = currentTime;

        if(window.GetKey(GLFW_KEY_UP) == GLFW_PRESS)
        {
            cameraDY = MOVE_SPEED;
        }
        else if(window.GetKey(GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            cameraDY = -MOVE_SPEED;
        }
        else
        {
            cameraDY = 0;
        }

        if(window.GetKey(GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            cameraDX = MOVE_SPEED;
        }
        else if(window.GetKey(GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            cameraDX = -MOVE_SPEED;
        }
        else
        {
            cameraDX = 0;
        }

        //if (cameraDX != 0 && cameraDY != 0)
        //{
        //    cameraDX = (cameraDX / cameraDX) * std::sqrt(MOVE_SPEED);
        //    cameraDY = (cameraDY / cameraDY) * std::sqrt(MOVE_SPEED);
        //}

        if (cameraX <= 0 && cameraDX < 0)
        {
            cameraX = 0;
            cameraDX = 0;
        }

        if (cameraX >= (WORLD_WIDTH_IN_TILES - VIEW_WIDTH_IN_TILES) && cameraDX > 0)
        {
            cameraX = WORLD_WIDTH_IN_TILES - VIEW_WIDTH_IN_TILES;
            cameraDX = -cameraDX;
        }

        if (cameraY <= 0 && cameraDY < 0)
        {
            cameraY = 0;
            cameraDY = 0;
        }

        if (cameraY >= (WORLD_HEIGHT_IN_TILES - VIEW_HEIGHT_IN_TILES) && cameraDY > 0)
        {
            cameraY = WORLD_HEIGHT_IN_TILES - VIEW_HEIGHT_IN_TILES;
            cameraDY = 0;
        }

        cameraX += cameraDX * deltaTime;
        cameraY += cameraDY * deltaTime;

        glm::mat4 projection = glm::ortho(cameraX, cameraX + VIEW_WIDTH_IN_TILES, cameraY, cameraY + VIEW_HEIGHT_IN_TILES,  -1.0f, 1.0f);
        shaderProgram.SetUniform("projection", projection);

        vertexArray.Draw();
    }

    return 0;
}
