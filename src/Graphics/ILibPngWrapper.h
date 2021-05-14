#pragma once

#include <cstddef>
#include <cstdint>

#include <png.h>

namespace Graphics
{
    class ILibPngWrapper
    {
    public:
        virtual int png_image_begin_read_from_file(png_image* image, const char *file_name) = 0;
        virtual int png_image_finish_read(png_image* image, png_color* background, void* buffer, int32_t row_stride, void* colormap) = 0;
        virtual size_t png_image_size(png_image& image) = 0;
        virtual size_t png_image_row_stride(png_image& image) = 0;

    protected:
        // This interface is not intended to expose ownership of the
        // concrete object implementing it.  Therefore, do not allow
        // deletion via interface pointers.
        ~ILibPngWrapper() = default;
    };
}
