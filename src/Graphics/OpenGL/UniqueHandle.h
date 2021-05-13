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
          : _handle(handle), _deleter(deleter)
        {

        }

        ~UniqueHandle()
        {
            reset();
        }

        UniqueHandle(const UniqueHandle<TDeleter>& other) = delete;
        UniqueHandle<TDeleter>& operator=(const UniqueHandle<TDeleter>& other) = delete;

        UniqueHandle(UniqueHandle<TDeleter>&& other)
        {
            _handle = other._handle;
            other._handle = 0;
            _deleter = other._deleter;
        }

        UniqueHandle<TDeleter>& operator=(UniqueHandle<TDeleter>&& other)
        {
            if (this == &other)
            {
                return *this;
            }

            reset(other._handle);
            other._handle = 0;
            _deleter = other._deleter;

            return *this;
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
