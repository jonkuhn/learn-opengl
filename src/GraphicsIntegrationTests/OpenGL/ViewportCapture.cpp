#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "ViewportCapture.h"

using namespace Graphics::OpenGL;

ViewportCapture::Dimensions ViewportCapture::GetViewportDimensions(IOpenGLWrapper& _gl)
{
    ViewportCapture::Dimensions viewport;
    _gl.GetIntegerv(GL_VIEWPORT, reinterpret_cast<GLint*>(&viewport));
    return viewport;
}

ViewportCapture::ViewportCapture(IOpenGLWrapper& gl)
    : _gl(gl),
      _dimensions(GetViewportDimensions(_gl)),
      _pixelData(_dimensions.width * _dimensions.height)
{
    _gl.ReadPixels(0, 0, _dimensions.width, _dimensions.height, GL_RGBA, GL_UNSIGNED_BYTE, _pixelData.data());
}

GLint ViewportCapture::Width()
{
    return _dimensions.width;
}

GLint ViewportCapture::Height()
{
    return _dimensions.height;
}

Pixel ViewportCapture::GetPixel(GLint x, GLint y)
{
    if (x < 0 || x >= _dimensions.width)
    {
        std::stringstream ss;
        ss << "GetPixel x argument (" << x << ") must be in range 0-" << (_dimensions.width - 1);
        throw std::out_of_range(ss.str());
    }

    if (y < 0 || y >= _dimensions.height)
    {
        std::stringstream ss;
        ss << "GetPixel y argument (" << y << ") must be in range 0-" << (_dimensions.height - 1);
        throw std::out_of_range(ss.str());
    }

    auto offset = x + y * _dimensions.width;

    return _pixelData[offset];
}

void ViewportCapture::SaveToFile(const std::string& filename)
{
    // Because of OpenGL's coordinate system this will be flipped vertically

    std::ofstream file;        
    file.open(filename, std::ios::out | std::ios::binary);        
    file.write(reinterpret_cast<const char *>(_pixelData.data()), _pixelData.size() * sizeof(Pixel));
    file.close();
}
