#pragma once

#include "IVertexArray.h"

namespace Graphics::OpenGL
{
    // Marker interface for vertex array instances that are
    // unit quads (x=0, y=0, z=0, width=1.0, height=1.0)
    class IUnitQuadVertexArray : public IVertexArray
    {

    };
}
