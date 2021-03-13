#pragma once
#include <iostream>

#include "Graphics/OpenGL/IOpenGLWrapper.h"

struct Pixel
{
    GLubyte r, g, b, a;

    Pixel()
        : r(0), g(0), b(0), a(0)
    {
    }

    Pixel(GLubyte r_, GLubyte g_, GLubyte b_, GLubyte a_)
        : r(r_), g(g_), b(b_), a(a_)
    {
    }

    bool operator==(const Pixel &other) const
    {
        return r == other.r && g == other.g && b == other.b && a == other.a;
    }
};

std::ostream& operator<<(std::ostream &strm, const Pixel &p);
