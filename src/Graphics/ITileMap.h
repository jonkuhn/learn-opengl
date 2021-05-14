#pragma once

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-volatile"
#include <glm/mat4x4.hpp>
#pragma clang diagnostic pop

namespace Graphics
{
    class ITileMap
    {
    public:
        void Draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);
    };
}
