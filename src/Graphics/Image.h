#pragma once

#include <string>
#include <vector>


namespace Graphics
{
    class ILibPngWrapper;

    class Image
    {
    public:
        Image(ILibPngWrapper& libPng, const std::string& filename);

        inline const uint8_t* Data() const { return _data.data(); }
        inline int Width() const { return _width; }
        inline int Height() const { return _height; }

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

        inline PixelFormat Format() const { return _pixelFormat; }

    private:
        ILibPngWrapper& _libPng;
        std::vector<uint8_t> _data;
        int _width;
        int _height;
        PixelFormat _pixelFormat;
    };
}