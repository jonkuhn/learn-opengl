#include <iostream>
#include <vector>
#include <string>

#include "Graphics/OpenGL/GlfwWrapper.h"
#include "Graphics/OpenGL/OpenGLWrapper.h"
#include "Graphics/OpenGL/Shader.h"
#include "Graphics/OpenGL/ShaderProgram.h"
#include "Graphics/OpenGL/VertexArray.h"
#include "Graphics/OpenGL/Window.h"

using namespace Graphics::OpenGL;

// settings
constexpr unsigned int SCR_WIDTH = 800;
constexpr unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = R"##RAW##(
#version 330 core
layout (location = 0) in vec3 aPos;
void main()
{
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)##RAW##";

const char *fragmentShaderSource = R"##RAW##(
#version 330 core
out vec4 FragColor;
void main()
{
   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
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

int main()
{
    GlfwWrapper glfw;
    GlfwWindow window(&glfw, SCR_WIDTH, SCR_HEIGHT, "Learn OpenGL");
    OpenGLWrapper gl;

    Shader vertexShader(gl, ShaderType::Vertex, vertexShaderSource);
    Shader fragmentShader(gl, ShaderType::Fragment, fragmentShaderSource);
    ShaderProgram shaderProgram(&gl, {&vertexShader, &fragmentShader});

    VertexArray<Vertex> vertexArray(
        &gl,
        VertexArray<Vertex>::Params(
            std::vector<Vertex>({
                { 0.5f,  0.5f, 0.0f },  // top right
                { 0.5f, -0.5f, 0.0f },  // bottom right
                {-0.5f, -0.5f, 0.0f },  // bottom left
                {-0.5f,  0.5f, 0.0f }   // top left 
            }))
            .AddAttribute(3)
            .TriangleElementIndices(
                std::vector<GLuint>({
                    0, 1, 3,  // first Triangle
                    1, 2, 3   // second Triangle
                }))
        );

    // Draw in wireframe polygons.
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (window.Update())
    {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.Use();

        vertexArray.Draw();
    }

    return 0;
}
