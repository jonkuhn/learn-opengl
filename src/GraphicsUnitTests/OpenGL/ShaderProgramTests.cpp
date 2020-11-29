#include <string>
#include <sstream>

#include <gtest/gtest.h>

#include "Graphics/OpenGL/ShaderProgram.h"
#include "MockOpenGLWrapper.h"
#include "MockShader.h"
#include "TestHelpers.h"

using namespace testing;
using namespace Graphics::OpenGL;

class ShaderProgramTests : public Test
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
};

TEST_F(ShaderProgramTests, Constructor_MakesCallsToCreateAndLinkProgram)
{
    EXPECT_CALL(_mockLib, CreateProgram()).WillOnce(Return(_testProgramHandle));
    EXPECT_CALL(_mockLib, AttachShader(_testProgramHandle, _testShaderHandleA));
    EXPECT_CALL(_mockLib, AttachShader(_testProgramHandle, _testShaderHandleB));
    EXPECT_CALL(_mockLib, LinkProgram(_testProgramHandle));
    EXPECT_CALL(_mockLib, GetProgramiv(_testProgramHandle, GL_LINK_STATUS, _))
        .WillOnce(SetArgPointee<2>(true));

    ShaderProgram shaderProgram(_mockLib, {&_mockShaderA, &_mockShaderB});
}

TEST_F(ShaderProgramTests, Constructor_GivenZeroShaders_ThrowsInvalidArgument)
{
    EXPECT_THROW(
        ShaderProgram shaderProgram(_mockLib, {}),
        std::invalid_argument
    );
}

TEST_F(ShaderProgramTests, Constructor_GivenCreateFails_ThrowsRuntimeErrorWithErrorCode)
{
    GLenum testError = 5555;
    EXPECT_CALL(_mockLib, CreateProgram()).WillOnce(Return(0));
    EXPECT_CALL(_mockLib, GetError()).WillOnce(Return(testError));
    EXPECT_THROW(
        try
        {
            ShaderProgram shaderProgram(_mockLib, {&_mockShaderA, &_mockShaderB});
        }
        catch(const std::runtime_error& e)
        {
            // Just assert that it contains the info log.  Currently it
            // also contains the source code, but that may change.
            std::stringstream ss;
            ss << testError;
            EXPECT_THAT(e.what(), HasSubstr(ss.str()));
            throw;
        },
        std::runtime_error);
}

TEST_F(ShaderProgramTests, Constructor_GivenLinkingFails_ThrowsRuntimeErrorWithInfoLog)
{
    const std::string testInfoLog("fake info log");
    EXPECT_CALL(_mockLib, CreateProgram()).WillOnce(Return(_testProgramHandle));
    EXPECT_CALL(_mockLib, GetProgramiv(_, GL_LINK_STATUS, _)).WillOnce(SetArgPointee<2>(false));
    EXPECT_CALL(_mockLib, GetProgramiv(_, GL_INFO_LOG_LENGTH, _)).WillOnce(SetArgPointee<2>(testInfoLog.size()));
    EXPECT_CALL(_mockLib, GetProgramInfoLog(_, _, _, _))
        .WillOnce(FillArgPointeeBuffer<3>(testInfoLog.c_str(), testInfoLog.size()));
    EXPECT_THROW(
        try
        {
            ShaderProgram shaderProgram(_mockLib, {&_mockShaderA, &_mockShaderB});
        }
        catch(const std::runtime_error& e)
        {
            // Just assert that it contains the info log.
            EXPECT_THAT(e.what(), HasSubstr(testInfoLog));
            throw;
        },
        std::runtime_error);
}

TEST_F(ShaderProgramTests, Destructor_CallsDeleteProgram)
{
    EXPECT_CALL(_mockLib, CreateProgram()).WillOnce(Return(_testProgramHandle));
    EXPECT_CALL(_mockLib, GetProgramiv(_, GL_LINK_STATUS, _)).WillOnce(SetArgPointee<2>(true));
    EXPECT_CALL(_mockLib, DeleteProgram(_testProgramHandle));

    {
        ShaderProgram shaderProgram(_mockLib, {&_mockShaderA, &_mockShaderB});
    }
}

TEST_F(ShaderProgramTests, Handle_ReturnsProgramHandle)
{
    EXPECT_CALL(_mockLib, CreateProgram()).WillOnce(Return(_testProgramHandle));
    EXPECT_CALL(_mockLib, GetProgramiv(_, GL_LINK_STATUS, _)).WillOnce(SetArgPointee<2>(true));
    ShaderProgram shaderProgram(_mockLib, {&_mockShaderA, &_mockShaderB});
    EXPECT_EQ(shaderProgram.Handle(), _testProgramHandle);
}
