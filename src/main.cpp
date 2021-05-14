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

//#include "Graphics/OpenGL/Factory.h"

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
    GlfwWindow window(&glfw, SCR_WIDTH, SCR_HEIGHT, "Learn OpenGL");
    OpenGLWrapper gl(&window);
    LibPngWrapper libpng;

    Shader vertexShader(&gl, Shader::Type::Vertex, vertexShaderSource);
    Shader fragmentShader(&gl, Shader::Type::Fragment, fragmentShaderSource);
    ShaderProgram shaderProgram(&gl, {&vertexShader, &fragmentShader});

    std::cout << reinterpret_cast<uintptr_t>(&glfw) << std::endl;
    std::cout << reinterpret_cast<uintptr_t>(&window) << std::endl;
    std::cout << reinterpret_cast<uintptr_t>(&gl) << std::endl;
    std::cout << reinterpret_cast<uintptr_t>(&libpng) << std::endl;
    std::cout << reinterpret_cast<uintptr_t>(&fragmentShader) << std::endl;
    std::cout << reinterpret_cast<uintptr_t>(&shaderProgram) << std::endl;
    std::cout << *(reinterpret_cast<uintptr_t*>(&glfw)) << std::endl;
    std::cout << *(reinterpret_cast<uintptr_t*>(&window)) << std::endl;
    std::cout << *(reinterpret_cast<uintptr_t*>(&gl)) << std::endl;
    std::cout << *(reinterpret_cast<uintptr_t*>(&libpng)) << std::endl;
    std::cout << *(reinterpret_cast<uintptr_t*>(&fragmentShader)) << std::endl;
    std::cout << *(reinterpret_cast<uintptr_t*>(&shaderProgram)) << std::endl;

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
    const float WORLD_WIDTH_IN_TILES = 100;
    const float WORLD_HEIGHT_IN_TILES = 100; 
    const float TILE_SET_WIDTH_IN_TILES = 2;
    const float TILE_SET_HEIGHT_IN_TILES = 2;
    //const float VIEW_WIDTH_IN_TILES = 10;
    //const float VIEW_HEIGHT_IN_TILES = 10;

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

    //auto view = glm::lookAt(
    //    glm::vec3(5.0f, 5.0f, 0.0f),
    //    glm::vec3(5.0f, 5.0f, 0.0f),
    //    glm::vec3(0.0f, 1.0f, 0.0f));
    //shaderProgram.SetUniform("view", view);

//    glm::vec3 direction;
//    float yaw = 150.0f;
//    float pitch = 0.0f;
//    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
//    direction.y = sin(glm::radians(pitch));
//    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
//    glm::vec3 cameraFront = glm::normalize(direction);
//
//    glm::vec3 cameraPos   = glm::vec3(5.0f, 5.0f,  3.0f);
//    //glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
//    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
//    auto view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
//    shaderProgram.SetUniform("view", view);

    //auto projection = glm::perspective(glm::radians(100.0f), 800.0f / 600.0f,  -1.0f, 1.0f);
    //shaderProgram.SetUniform("projection", projection);

    //glEnable(GL_BLEND);

    RandomTileMap randomTileMap(WORLD_WIDTH_IN_TILES, WORLD_HEIGHT_IN_TILES);
    Texture tileMap(&gl, Texture::Params(randomTileMap)
        .WrapModeS(Texture::WrapMode::ClampToBorder)
        .WrapModeT(Texture::WrapMode::ClampToBorder)
        .MinFilter(Texture::MinFilterMode::Nearest)
        .MagFilter(Texture::MagFilterMode::Nearest));

    PngImage tileAtlasImage(&libpng, "TestFiles/scribbletiles.png");
    Texture tileAtlas(&gl, Texture::Params(tileAtlasImage)
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

        //if (cameraX <= 0 && cameraDX < 0)
        //{
        //    cameraX = 0;
        //    cameraDX = 0;
        //}

        //if (cameraX >= (WORLD_WIDTH_IN_TILES - VIEW_WIDTH_IN_TILES) && cameraDX > 0)
        //{
        //    cameraX = WORLD_WIDTH_IN_TILES - VIEW_WIDTH_IN_TILES;
        //    cameraDX = -cameraDX;
        //}

        //if (cameraY <= 0 && cameraDY < 0)
        //{
        //    cameraY = 0;
        //    cameraDY = 0;
        //}

        //if (cameraY >= (WORLD_HEIGHT_IN_TILES - VIEW_HEIGHT_IN_TILES) && cameraDY > 0)
        //{
        //    cameraY = WORLD_HEIGHT_IN_TILES - VIEW_HEIGHT_IN_TILES;
        //    cameraDY = 0;
        //}

        cameraX += cameraDX * deltaTime;
        cameraY += cameraDY * deltaTime;

        //auto projection = glm::ortho(cameraX, cameraX + VIEW_WIDTH_IN_TILES, cameraY, cameraY + VIEW_HEIGHT_IN_TILES,  -1.0f, 1.0f);
        ////projection = glm::rotate(projection, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        //shaderProgram.SetUniform("projection", projection);

        // 2D Camera
        // Notes:
        // - Z component of cameraPosition must be such that the objects
        //   that should be visible are within the range of zNear to zFar
        //   from the camera.  (where zNear and zFar are the arguments to
        //   glm::ortho).  If zNear is negative objects behind the camera
        //   will be rendered.
        // - In order for the center argument to lookAt (cameraPos + cameraFront)
        //   to truly be centered in the window, the left and right and
        //   top and bottom arguments to glm::ortho must be set such that
        //   0 is the midpoint (i.e. left = -right bottom = -top)
        // - cameraFront is a normalized vector that represents the direction
        //   the camera is pointing
        // - cameraUp is a normalized vector that points to the up direction
        //   in world space.  glm::lookAt uses this together with "center"
        //   (the direction the camera is pointing -- cameraPos + cameraFront)
        //   to get a vector that points to the right in view space.  This is
        //   done by taking the cross product of the two to get an orthogonal
        //   vector.  glm::lookAt then takes the cross product of resulting
        //   "right" vector and the vector representing the direction the
        //   camera is pointing to get the "up" vector which is a vector
        //   pointing out of the top of the camera.  The actual matrix
        //   returned by glm::lookAt is built from the "direction", "right",
        //   and "up" vectors (note "up" != cameraUp)
        //   (See https://learnopengl.com/Getting-started/Camera)
        glm::vec3 cameraPos   = glm::vec3(cameraX, cameraY, 0.5f);
        glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
        auto view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        shaderProgram.SetUniform("view", view);
        auto projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f,  0.0f, 1.0f);
        shaderProgram.SetUniform("projection", projection);

        // 3D Camera
        // Notes:
        //
        //glm::vec3 cameraPos   = glm::vec3(cameraX, cameraY, 3.0f);
        //glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        //glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
        //auto view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        //shaderProgram.SetUniform("view", view);
        //auto projection = glm::perspective(glm::radians(100.0f), 800.0f / 600.0f,  0.1f, 1.0f);
        //shaderProgram.SetUniform("projection", projection);

        //glm::vec3 cameraPos   = glm::vec3(cameraX + 5.0f, cameraY + 5.0f,  3.0f);
        //glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        //glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
        //auto view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        //shaderProgram.SetUniform("view", view);

        //glm::vec3 direction;
        //float yaw = -90.0f;
        //float pitch = 0.0f;
        //direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        //direction.y = sin(glm::radians(pitch));
        //direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        //glm::vec3 cameraFront = glm::normalize(direction);

        //glm::vec3 cameraPos   = glm::vec3(cameraX + 5.0f, cameraY + 5.0f,  3.0f);
        //glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        //glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
        //auto view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        //shaderProgram.SetUniform("view", view);

        vertexArray.Draw();
    }

    return 0;
}
