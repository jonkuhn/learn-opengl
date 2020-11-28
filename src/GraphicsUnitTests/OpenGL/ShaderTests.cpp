#include <string>
#include <sstream>

#include <gtest/gtest.h>

#include "MockOpenGLWrapper.h"
#include "Graphics/OpenGL/Shader.h"

using namespace testing;
using namespace Graphics::OpenGL;

class ShaderTests : public Test
{
public:
    ShaderTests()
        : _testSource("fake source code")
    {

    }

protected:
    void SetupMockCreateToAlwaysSucceed()
    {
        EXPECT_CALL(_mockLib, CreateShader(_)).WillRepeatedly(Return(_testHandle));
    }

    void SetupMockCompileToAlwaysSucceed()
    {
        EXPECT_CALL(_mockLib, GetShaderiv(_, GL_COMPILE_STATUS, _)).WillRepeatedly(SetArgPointee<2>(true));
    }

    NiceMock<MockOpenGLWrapper> _mockLib;
    const GLuint _testHandle = 456;
    const std::string _testSource;
};

MATCHER_P(DoublePtrStrEq, expectedStr, "") { return expectedStr == std::string(*arg); }

ACTION_TEMPLATE(FillArgPointeeBuffer, HAS_1_TEMPLATE_PARAMS(unsigned, argIndex), AND_2_VALUE_PARAMS(srcBuffer, srcSize))
{
    std::memcpy(std::get<argIndex>(args), srcBuffer, srcSize);
}

TEST_F(ShaderTests, Constructor_MakesCallsToCreateAndCompileShader)
{
    EXPECT_CALL(_mockLib, CreateShader(_)).WillOnce(Return(_testHandle));
    EXPECT_CALL(_mockLib, ShaderSource(_testHandle, 1, DoublePtrStrEq(_testSource), nullptr));
    EXPECT_CALL(_mockLib, CompileShader(_testHandle));
    EXPECT_CALL(_mockLib, GetShaderiv(_testHandle, GL_COMPILE_STATUS, _))
        .WillOnce(SetArgPointee<2>(true));

    Shader shader(_mockLib, Shader::Type::Vertex, _testSource);
}

TEST_F(ShaderTests, Constructor_CallsCreateShaderWithExpectedType)
{
    SetupMockCompileToAlwaysSucceed();

    EXPECT_CALL(_mockLib, CreateShader(GL_VERTEX_SHADER)).WillOnce(Return(_testHandle));
    Shader vertexShader(_mockLib, Shader::Type::Vertex, _testSource);

    EXPECT_CALL(_mockLib, CreateShader(GL_FRAGMENT_SHADER)).WillOnce(Return(_testHandle));
    Shader fragmentShader(_mockLib, Shader::Type::Fragment, _testSource);
}

TEST_F(ShaderTests, ConstructFromStream_PassesSourceCorrectly)
{
    SetupMockCreateToAlwaysSucceed();
    SetupMockCompileToAlwaysSucceed();

    EXPECT_CALL(_mockLib, ShaderSource(_, 1, DoublePtrStrEq(_testSource), nullptr));

    std::stringstream sourceStream(_testSource);
    Shader shader(_mockLib, Shader::Type::Vertex, sourceStream);
}

TEST_F(ShaderTests, Constructor_GivenCompilationFails_ThrowsRuntimeErrorWithInfoLog)
{
    const std::string testInfoLog("fake info log");
    EXPECT_CALL(_mockLib, CreateShader(_)).WillOnce(Return(_testHandle));
    EXPECT_CALL(_mockLib, GetShaderiv(_, GL_COMPILE_STATUS, _)).WillOnce(SetArgPointee<2>(false));
    EXPECT_CALL(_mockLib, GetShaderiv(_, GL_INFO_LOG_LENGTH, _)).WillOnce(SetArgPointee<2>(testInfoLog.size()));
    EXPECT_CALL(_mockLib, GetShaderInfoLog(_, _, _, _))
        .WillOnce(FillArgPointeeBuffer<3>(testInfoLog.c_str(), testInfoLog.size()));
    EXPECT_THROW(
        try
        {
            Shader shader(_mockLib, Shader::Type::Vertex, _testSource);
        }
        catch(const std::runtime_error& e)
        {
            // Just assert that it contains the info log.  Currently it
            // also contains the source code, but that may change.
            EXPECT_THAT(e.what(), HasSubstr(testInfoLog));
            throw;
        },
        std::runtime_error);
}

TEST_F(ShaderTests, Destructor_CallsDeleteShader)
{
    EXPECT_CALL(_mockLib, CreateShader(_))
        .WillOnce(Return(_testHandle));
    EXPECT_CALL(_mockLib, DeleteShader(_testHandle));

    {
        Shader shader(_mockLib, Shader::Type::Vertex, _testSource);
    }
}

TEST_F(ShaderTests, Handle_ReturnsShaderHandle)
{
    SetupMockCreateToAlwaysSucceed();
    SetupMockCompileToAlwaysSucceed();

    Shader shader(_mockLib, Shader::Type::Vertex, _testSource);
    EXPECT_EQ(shader.Handle(), _testHandle);
}