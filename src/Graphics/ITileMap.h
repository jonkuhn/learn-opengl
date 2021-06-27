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
        virtual void Draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) = 0;

    protected:
        // This interface is not intended to expose ownership of the
        // concrete object implementing it.  Therefore, do not allow
        // deletion via interface pointers.
        ~ITileMap() = default;
    };
}
