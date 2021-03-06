#pragma once

#include <cstddef>

namespace Graphics
{
    class IImage
    {
    public:
        virtual const uint8_t* Data() const = 0;
        virtual int Width() const = 0;
        virtual int Height() const = 0;

        // Currently only RGBA is used but this exists for
        // future flexibility
        enum class PixelFormat
        {
            Invalid,
            Grayscale,
            GrayscaleAlpha,
            RGB,
            RGBA,
        };

        virtual PixelFormat Format() const = 0;

    protected:
        // This interface is not intended to expose ownership of the
        // concrete object implementing it.  Therefore, do not allow
        // deletion via interface pointers.
        ~IImage() = default;
    };
}
