#pragma once

#include "IUnitQuadVertexArray.h"
#include "IVertexArray.h"

namespace Graphics::OpenGL
{
    // Vertex array that is a unit quad (x=0, y=0, z=0, width=1.0, height=1.0)
    class UnitQuadVertexArray final : public IUnitQuadVertexArray
    {
    public:
        UnitQuadVertexArray(IVertexArray* vertexArray)
            : _vertexArray(vertexArray)
        {

        }

        void Draw() override
        {
            _vertexArray->Draw();
        };

    private:
        IVertexArray* _vertexArray;
    };
}
