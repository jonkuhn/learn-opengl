#pragma once

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-volatile"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#pragma clang diagnostic pop

class Camera2d
{
public:
    Camera2d()
    {
        _cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        _cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
    }

    inline void Position(glm::vec3 position)
    {
        _position = std::move(position);
        _viewMatrix = glm::lookAt(_position, _position + _cameraFront, _cameraUp);
    }

    inline const glm::vec3& Position()
    {
        return _position;
    }

    inline void FieldOfView(float left, float right, float bottom, float top, float near, float far)
    {
        _projectionMatrix = glm::ortho(left, right, bottom, top, near, far);
    }

    inline const glm::mat4& ViewMatrix()
    {
        return _viewMatrix;
    }

    inline const glm::mat4& ProjectionMatrix()
    {
        return _projectionMatrix;
    }

private:
    glm::vec3 _position;
    glm::vec3 _cameraFront;
    glm::vec3 _cameraUp;
    glm::mat4 _viewMatrix;
    glm::mat4 _projectionMatrix;
};
