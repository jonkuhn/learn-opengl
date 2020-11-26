#pragma once
#include <istream>

#include "LibraryWrapper.h"

namespace Graphics::OpenGL
{
    class Shader
    {
    public:
        enum class Type
        {
            Vertex,
            Fragment
        };

        Shader(ILibraryWrapper& lib, Type type, std::istream& sourceStream);
        Shader(ILibraryWrapper& lib, Type type, const std::string& source);
        ~Shader();

        GLuint Handle();

    private:
        ILibraryWrapper& _lib;
        GLuint _handle;
    };
}