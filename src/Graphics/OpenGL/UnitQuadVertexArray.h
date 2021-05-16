#pragma once

#include "IUnitQuadVertexArray.h"
#include "VertexArray.h"

namespace Graphics::OpenGL
{
    // Vertex array that is a unit quad (x=0, y=0, z=0, width=1.0, height=1.0)
    class UnitQuadVertexArray final : public IUnitQuadVertexArray
    {
    public:
        UnitQuadVertexArray(IOpenGLWrapper* gl)
            : _vertexArray(
                gl,
                VertexArray<Vertex>::Params(
                    std::vector<Vertex>({
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
            )
        {

        }

        void Draw() override
        {
            _vertexArray.Draw();
        };

    private:
        struct Vertex
        {
            float x;
            float y;
            float z;
        };
        VertexArray<Vertex> _vertexArray;
    };
}
