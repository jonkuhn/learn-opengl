#pragma once

namespace Graphics::OpenGL
{
    class ITexture
    {
    public:
        virtual void Bind(int textureIndex) = 0;

    protected:
        // This interface is not intended to expose ownership of the
        // concrete object implementing it.  Therefore, do not allow
        // deletion via interface pointers.
        ~ITexture() = default;
    };
}