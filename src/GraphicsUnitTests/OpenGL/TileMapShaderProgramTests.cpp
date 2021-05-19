#include <memory>
#include <string>
#include <sstream>

#include <gtest/gtest.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-volatile"
#include <glm/gtc/type_ptr.hpp>
#pragma clang diagnostic pop

#include "Graphics/OpenGL/ShaderProgram.h"
#include "MockOpenGLWrapper.h"
#include "MockShader.h"
#include "../TestHelpers.h"

using namespace testing;
using namespace Graphics::OpenGL;

class TileMapShaderProgramTests : public Test
{
public:
    ShaderProgramTests()
    {
        EXPECT_CALL(_mockShaderA, Handle()).WillRepeatedly(Return(_testShaderHandleA));
        EXPECT_CALL(_mockShaderB, Handle()).WillRepeatedly(Return(_testShaderHandleB));
    }

protected:
    NiceMock<MockOpenGLWrapper> _mockLib;
    const GLuint _testShaderHandleA = 123;
    const GLuint _testShaderHandleB = 456;
    const GLuint _testProgramHandle = 789;
    MockShader _mockShaderA;
    MockShader _mockShaderB;

    std::unique_ptr<ShaderProgram> CreateTestShaderProgram()
    {
        EXPECT_CALL(_mockLib, CreateProgram()).WillOnce(Return(_testProgramHandle));
        EXPECT_CALL(_mockLib, GetProgramiv(_, GL_LINK_STATUS, _)).WillOnce(SetArgPointee<2>(true));
        return std::make_unique<ShaderProgram>(&_mockLib, std::initializer_list<IShader*>({&_mockShaderA, &_mockShaderB}));
    }

    std::tuple<std::unique_ptr<ShaderProgram>,
        std::unique_ptr<ShaderProgram>> GetTwoShaderProgramsWithHandles(GLuint handleA, GLuint handleB)
    {
        Sequence seq;
        EXPECT_CALL(_mockLib, CreateProgram()).InSequence(seq).WillOnce(Return(handleA));
        EXPECT_CALL(_mockLib, GetProgramiv(_, GL_LINK_STATUS, _)).InSequence(seq).WillOnce(SetArgPointee<2>(true));
        EXPECT_CALL(_mockLib, CreateProgram()).InSequence(seq).WillOnce(Return(handleB));
        EXPECT_CALL(_mockLib, GetProgramiv(_, GL_LINK_STATUS, _)).InSequence(seq).WillOnce(SetArgPointee<2>(true));

        auto programA = std::unique_ptr<ShaderProgram>(new ShaderProgram(&_mockLib, {&_mockShaderA, &_mockShaderB}));
        auto programB = std::unique_ptr<ShaderProgram>(new ShaderProgram(&_mockLib, {&_mockShaderA, &_mockShaderB}));

        Mock::VerifyAndClear(&_mockLib);

        return std::tuple(std::move(programA), std::move(programB));
    }

};

TEST_F(TileMapShaderProgramTests, Constructor_MakesCallsToCreateAndLinkProgram)
{
    Sequence s1, s2, s3, s4, s5;
    EXPECT_CALL(_mockLib, CreateProgram()).InSequence(s1, s2).WillOnce(Return(_testProgramHandle));
    EXPECT_CALL(_mockLib, AttachShader(_testProgramHandle, _testShaderHandleA)).InSequence(s1);
    EXPECT_CALL(_mockLib, AttachShader(_testProgramHandle, _testShaderHandleB)).InSequence(s2);
    EXPECT_CALL(_mockLib, LinkProgram(_testProgramHandle)).InSequence(s1, s2);
    EXPECT_CALL(_mockLib, GetProgramiv(_testProgramHandle, GL_LINK_STATUS, _))
        .InSequence(s1, s2).WillOnce(SetArgPointee<2>(true));
    EXPECT_CALL(_mockLib, DetachShader(_testProgramHandle, _testShaderHandleA)).InSequence(s1);
    EXPECT_CALL(_mockLib, DetachShader(_testProgramHandle, _testShaderHandleB)).InSequence(s2);

    ShaderProgram shaderProgram(&_mockLib, {&_mockShaderA, &_mockShaderB});
}