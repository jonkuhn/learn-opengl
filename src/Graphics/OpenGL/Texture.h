#pragma once
#include <string>

#include "../IImage.h"

#include "IOpenGLWrapper.h"

namespace Graphics::OpenGL
{
    class Texture
    {
    public:
        enum class WrapMode
        {
            ClampToEdge,
            ClampToBorder,
            MirroredRepeat,
            Repeat,
        };

        enum class MinFilterMode
        {
            Nearest,
            Linear,
            NearestMipmapNearest,
            LinearMipmapNearest,
            NearestMipmapLinear,
            LinearMipmapLinear,
        };

        enum class MagFilterMode
        {
            Nearest,
            Linear,
        };

        class Params
        {
        public:
            Params(const IImage& image_);
            Params& WrapModeS(WrapMode wrapModeS_);
            Params& WrapModeT(WrapMode wrapModeT_);
            Params& MinFilter(MinFilterMode minFilter_);
            Params& MagFilter(MagFilterMode magFilter_);

            const IImage& image;
            WrapMode wrapModeS;
            WrapMode wrapModeT;
            MinFilterMode minFilter;
            MagFilterMode magFilter;
        };

        Texture(IOpenGLWrapper& gl, const Params& params);
        ~Texture();

        void Bind();

    private:
        IOpenGLWrapper& _gl;
        GLuint _handle;
    };
}
