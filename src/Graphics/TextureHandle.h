#pragma once

namespace Graphics
{
    struct TextureHandle
    {
        TextureHandle(void* p_)
        {
            p = p_;
        }
        void* p;
    };
}