#pragma once

namespace Graphics::OpenGL
{
    class ITexture
    {
    public:
        void Bind(int textureIndex);

    protected:
        // This interface is not intended to expose ownership of the
        // concrete object implementing it.  Therefore, do not allow
        // deletion via interface pointers.
        ~ITexture() = default;
    };
}