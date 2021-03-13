#pragma once
#include <string>
#include <vector>

#include "Graphics/OpenGL/IOpenGLWrapper.h"

#include "Pixel.h"

class ViewportCapture
{
public:
    ViewportCapture(Graphics::OpenGL::IOpenGLWrapper& gl);
    GLint Width();
    GLint Height();
    Pixel GetPixel(GLint x, GLint y);
    void SaveToFile(const std::string& filename);

private:
    struct Dimensions
    {
        GLint x, y, width, height;
    };

    Graphics::OpenGL::IOpenGLWrapper& _gl;
    Dimensions _dimensions;
    std::vector<Pixel> _pixelData;

    static Dimensions GetViewportDimensions(Graphics::OpenGL::IOpenGLWrapper& _gl);
};
