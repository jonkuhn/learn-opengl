#pragma once

#include <memory>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-volatile"
#include <glm/vec3.hpp>
#pragma clang diagnostic pop

#include "IImage.h"
#include "ITileMap.h"
#include "TextureHandle.h"

namespace Graphics
{
    class IFactory
    {
    public:
        virtual TextureHandle CreateTexture(IImage& image) = 0;
        virtual ITileMap* CreateTileMap(
            TextureHandle tileMap,
            const glm::vec2& mapSizeInTiles,
            TextureHandle tileAtlas,
            const glm::vec2& atlasSizeInTiles) = 0;

    protected:
        // This interface is not intended to expose ownership of the
        // concrete object implementing it.  Therefore, do not allow
        // deletion via interface pointers.
        ~IFactory() = default;
    };
}
