#include <gtest/gtest.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-volatile"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#pragma clang diagnostic pop

#include "Graphics/ObjectInstance2d.h"
#include "TestHelpers.h"

using namespace testing;
using namespace Graphics;

class ObjectInstance2dTests : public Test
{

};

TEST_F(ObjectInstance2dTests, Constructor_ModelMatrixHasPositionAtOriginRotation0And1by1Size)
{
    ObjectInstance2d obj;

    auto actual = obj.ModelMatrix();

    auto expected = glm::mat4(1.0f);
    expected = glm::translate(expected, glm::vec3(0.0f, 0.0f, 0.0f));
    expected = glm::rotate(expected, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, -1.0f));  
    expected = glm::scale(expected, glm::vec3(1.0f, 1.0f, 0.0f));  
    ExpectEqual(actual, expected);
}

TEST_F(ObjectInstance2dTests, Position_GivenPositionChangeAfterFetchingModelMatrix_ModelMatrixMatchesUpdatedPosition)
{
    glm::vec3 testPosition(128.5f, 64.125f, -0.25f);
    ObjectInstance2d obj;
    // fetch to ensure model matrix would be cached with default values
    obj.ModelMatrix();

    obj.Position(testPosition);

    auto actual = obj.ModelMatrix();
    auto expected = glm::mat4(1.0f);
    expected = glm::translate(expected, testPosition);
    expected = glm::rotate(expected, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, -1.0f));  
    expected = glm::scale(expected, glm::vec3(1.0f, 1.0f, 0.0f));  

    ExpectEqual(actual, expected);
}

TEST_F(ObjectInstance2dTests, Size_GivenSizeChangedAfterFetchingModelMatrix_ModelMatrixMatchesUpdatedSize)
{
    glm::vec2 testSize(12.25, 6.5);
    ObjectInstance2d obj;
    // fetch to ensure model matrix would be cached with default values
    obj.ModelMatrix();

    obj.Size(testSize);

    auto actual = obj.ModelMatrix();
    auto expected = glm::mat4(1.0f);
    expected = glm::translate(expected, glm::vec3(0.0f, 0.0f, 0.0f));
    expected = glm::rotate(expected, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, -1.0f));  
    expected = glm::scale(expected, glm::vec3(testSize.x, testSize.y, 0.0f));  

    ExpectEqual(actual, expected);
}

TEST_F(ObjectInstance2dTests, Rotation_GivenRotationChangedAfterFetchingModelMatrix_ModelMatrixMatchesUpdatedRotation)
{
    float testRotationDegrees = 12.5;
    ObjectInstance2d obj;
    // fetch to ensure model matrix would be cached with default values
    obj.ModelMatrix();

    obj.Rotation(testRotationDegrees);

    auto actual = obj.ModelMatrix();
    auto expected = glm::mat4(1.0f);
    expected = glm::translate(expected, glm::vec3(0.0f, 0.0f, 0.0f));
    expected = glm::rotate(expected, glm::radians(testRotationDegrees), glm::vec3(0.0f, 0.0f, -1.0f));  
    expected = glm::scale(expected, glm::vec3(1.0f, 1.0f, 0.0f));  

    ExpectEqual(actual, expected);
}

TEST_F(ObjectInstance2dTests, ModelMatrix_GivenNonZeroPositionScaleAndRotation_ModelMatrixIsCorrect)
{
    glm::vec3 testPosition(128.5f, 64.125f, -0.25f);
    glm::vec2 testSize(12.25, 6.5);
    float testRotationDegrees = 12.5;
    ObjectInstance2d obj;
    // fetch to ensure model matrix would be cached with default values
    obj.ModelMatrix();

    obj.Rotation(testRotationDegrees);
    obj.Position(testPosition);
    obj.Size(testSize);

    auto actual = obj.ModelMatrix();
    auto expected = glm::mat4(1.0f);
    expected = glm::translate(expected, testPosition);
    expected = glm::rotate(expected, glm::radians(testRotationDegrees), glm::vec3(0.0f, 0.0f, -1.0f));  
    expected = glm::scale(expected, glm::vec3(testSize.x, testSize.y, 0.0f));  

    ExpectEqual(actual, expected);
}
