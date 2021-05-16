#pragma once

namespace Graphics::OpenGL
{
    class IVertexArray
    {
    public:
        virtual void Draw() = 0;

    protected:
        // This interface is not intended to expose ownership of the
        // concrete object implementing it.  Therefore, do not allow
        // deletion via interface pointers.
        ~IVertexArray() = default;
    };
}
