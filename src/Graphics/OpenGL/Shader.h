#pragma once
#include <istream>

#include <glad/glad.h>

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

        Shader(Type type, std::istream& sourceStream);
        Shader(Type type, const std::string& source);
        ~Shader();

        GLuint Handle();

    private:
        GLuint _handle;
    };
}