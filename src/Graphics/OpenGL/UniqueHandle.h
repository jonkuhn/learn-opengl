#pragma once
#include <glad/glad.h>

namespace Graphics::OpenGL
{
    template<typename TDeleter>
    class UniqueHandle
    {
    public:
        typedef void (*Deleter)(GLuint);

        UniqueHandle(GLuint handle, TDeleter deleter)
        {
            _handle = handle;
            _deleter = deleter;
        }

        ~UniqueHandle()
        {
            reset();
        }

        GLuint get()
        {
            return _handle;
        }

        void reset(GLuint h = 0)
        {
            if (_handle != 0)
            {
                _deleter(_handle);
            }
            _handle = h;
        }

    private:
        GLuint _handle;
        TDeleter _deleter;
    };
}
