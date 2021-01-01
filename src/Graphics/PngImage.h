#pragma once

#include <string>
#include <vector>

#include "IImage.h"

namespace Graphics
{
    class ILibPngWrapper;

    class PngImage : public IImage
    {
    public:
        PngImage(ILibPngWrapper& libPng, const std::string& filename);

        const uint8_t* Data() const;
        int Width() const;
        int Height() const;
        IImage::PixelFormat Format() const;

    private:
        ILibPngWrapper& _libPng;
        std::vector<uint8_t> _data;
        int _width;
        int _height;
        PixelFormat _pixelFormat;
    };
}
