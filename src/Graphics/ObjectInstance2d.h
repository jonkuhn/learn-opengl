#pragma once

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-volatile"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#pragma clang diagnostic pop

namespace Graphics
{
    class ObjectInstance2d
    {
    public:
        ObjectInstance2d()
        : _position(0.0f, 0.0f, 0.0f),
            _size(1.0f, 1.0f),
            _rotationDegrees(0.0f),
            _model(),
            _modelNeedsUpdated(true)
        {

        }

        inline void Position(glm::vec3 position)
        {
            _modelNeedsUpdated = true;
            _position = std::move(position);
        }

        inline void Size(glm::vec2 size)
        {
            _modelNeedsUpdated = true;
            _size = std::move(size);
        }

        inline void Rotation(float rotationDegrees)
        {
            _modelNeedsUpdated = true;
            _rotationDegrees = rotationDegrees;
        }

        inline const glm::mat4& ModelMatrix()
        {
            EnsureModelMatrixIsUpdated();
            return _model;
        }

    private:
        glm::vec3 _position;
        glm::vec2 _size;
        float _rotationDegrees;
        glm::mat4 _model;  
        bool _modelNeedsUpdated;

        inline void EnsureModelMatrixIsUpdated()
        {
            if (!_modelNeedsUpdated)
            {
                return;
            }

            // The order here is very important.  Transformations take place
            // in the opposite order in which they appear here.
            _model = glm::mat4(1.0f);
            _model = glm::translate(_model, _position);
            _model = glm::rotate(_model, glm::radians(_rotationDegrees), glm::vec3(0.0f, 0.0f, -1.0f));  
            _model = glm::scale(_model, glm::vec3(_size.x, _size.y, 0.0f));  

            _modelNeedsUpdated = false;
        }
    };
}
