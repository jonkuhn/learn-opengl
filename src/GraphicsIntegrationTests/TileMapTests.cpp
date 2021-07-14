#include <memory>

#include <gtest/gtest.h>

#include "Graphics/Graphics.h"

using namespace testing;
using namespace Graphics;

namespace
{
    constexpr unsigned int WINDOW_WIDTH = 800;
    constexpr unsigned int WINDOW_HEIGHT = 600;



    class TestTileMap : public IImage
    {
    public:
        TestTileMap()
            : _pixels({})
        {
        }

        const uint8_t* Data() const override
        {
            return &_pixels[0];
        }
        int Width() override
        {
            return 4;
        }

        int Height() override
        {
            return 4;
        }

        PixelFormat Format() override
        {
            PixelFormat::RGBA
        }
    private:
        // 16x16x4 array
        std::array<std::array<std::array<uint8_t, 4>,16>, 16> _pixels;
    };
}

class TileMapTests : public Test
{
public:
    TileMapTests()
        : _engine(new OpenGL::Engine(WINDOW_WIDTH, WINDOW_HEIGHT, "TileMapTests"))
    {

    }
protected:
    std::unique_ptr<IEngine> _engine;
};

TEST_F(TileMapTests, GivenSolidColored4x4TileAtlas_AssignedInDifferentOrderIn16x16TileMap_ColorSamplesMatchExpectations)
{

    PngImage colorTiles4x4(&_libpng, "TestFiles/colortiles4x4.png");
    auto atlas = _engine->CreateTileAtlas(colorTiles4x4, glm::vec2(4.0f, 4.0f));
    atlas->CreateTileMap()
}
