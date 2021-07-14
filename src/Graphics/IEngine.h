#pragma once

#include <memory>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-volatile"
#include <glm/glm.hpp>
#pragma clang diagnostic pop

#include "IImage.h"
#include "ITileAtlas.h"

namespace Graphics
{
    class IEngine
    {
    public:
        ~IEngine() = default;

        virtual std::unique_ptr<ITileAtlas> CreateTileAtlas(
            IImage &tileAtlas,
            const glm::vec2& atlasSizeInTiles) = 0;

    protected:
    };
}
