#include <stdexcept>
#include <string>
#include <sstream>

#include <gtest/gtest.h>

#include "Graphics/PngImage.h"
#include "MockLibPngWrapper.h"
#include "TestHelpers.h"

using namespace testing;
using namespace Graphics;

namespace
{
    ACTION_TEMPLATE(SetMessageOnPngImageArg, HAS_1_TEMPLATE_PARAMS(unsigned, argIndex), AND_1_VALUE_PARAMS(message))
    {
        std::strncpy(std::get<argIndex>(args)->message, message, 63);
        std::get<argIndex>(args)->message[63] = '\0';
    }

    ACTION_TEMPLATE(SetWidthAndHeightOnPngImageArg, HAS_1_TEMPLATE_PARAMS(unsigned, argIndex), AND_2_VALUE_PARAMS(width, height))
    {
        std::get<argIndex>(args)->width = width;
        std::get<argIndex>(args)->height = height;
    }
}

class PngImageTests : public Test
{
public:
    PngImageTests()
        : _testFilename("test-filename.png"),
          _testErrorMessage("test-error-message")
    {

    }

protected:
    NiceMock<MockLibPngWrapper> _mockLib;
    std::string _testFilename;
    const int32_t _testImageSize = 12345;
    const int _testWidth = 777;
    const int _testHeight = 888;
    std::string _testErrorMessage;
};

TEST_F(PngImageTests, Constructor_MakesCallsToLoadPng)
{
    // These will be pointers to a local variable in the constructor.
    // Therefore, only check them for equality, do not dereference
    // them in the test because they will no longer be valid
    png_image* capturedImagePtr1 = nullptr;
    png_image* capturedImagePtr2 = nullptr;
    png_image* capturedImagePtr3 = nullptr;

    EXPECT_CALL(_mockLib, png_image_begin_read_from_file(_, StrEq(_testFilename.c_str())))
        .WillOnce(DoAll(SaveArg<0>(&capturedImagePtr1), Return(true)));
    EXPECT_CALL(_mockLib, png_image_size(_))
        .WillOnce(DoAll(SavePointerToArgReferee<0>(&capturedImagePtr2), Return(_testImageSize)));
    EXPECT_CALL(_mockLib, png_image_finish_read(_, Eq(nullptr), Ne(nullptr), Eq(0), Eq(nullptr)))
        .WillOnce(DoAll(SaveArg<0>(&capturedImagePtr3), Return(true)));

    PngImage image(_mockLib, _testFilename);

    EXPECT_EQ(capturedImagePtr1, capturedImagePtr2);
    EXPECT_EQ(capturedImagePtr1, capturedImagePtr3);
}

TEST_F(PngImageTests, Constructor_SetsWidthHeightAndPixelFormat)
{
    EXPECT_CALL(_mockLib, png_image_begin_read_from_file(_, StrEq(_testFilename.c_str())))
        .WillOnce(Return(true));
    EXPECT_CALL(_mockLib, png_image_size(_))
        .WillOnce(Return(_testImageSize));
    EXPECT_CALL(_mockLib, png_image_finish_read(_, Eq(nullptr), Ne(nullptr), Eq(0), Eq(nullptr)))
        .WillOnce(DoAll(SetWidthAndHeightOnPngImageArg<0>(_testWidth, _testHeight), Return(true)));

    PngImage image(_mockLib, _testFilename);

    EXPECT_EQ(image.Width(), _testWidth);
    EXPECT_EQ(image.Height(), _testHeight);

    // Currently expect all images to be in RGBA format once loaded
    EXPECT_EQ(image.Format(), PngImage::PixelFormat::RGBA);
}

TEST_F(PngImageTests, Constructor_BeginReadFails_ThrowsRuntimeErrorContainingMessage)
{
    EXPECT_CALL(_mockLib, png_image_begin_read_from_file(_, _))
        .WillOnce(DoAll(SetMessageOnPngImageArg<0>(_testErrorMessage.c_str()), Return(false)));
    EXPECT_THROW(
        try
        {
            PngImage image(_mockLib, _testFilename);
        }
        catch(const std::runtime_error& e)
        {
            EXPECT_THAT(e.what(), HasSubstr("begin"));
            EXPECT_THAT(e.what(), HasSubstr(_testErrorMessage));
            throw;
        },
        std::runtime_error);
}

TEST_F(PngImageTests, Constructor_FinishReadFails_ThrowsRuntimeErrorContainingMessage)
{
    EXPECT_CALL(_mockLib, png_image_begin_read_from_file(_, _))
        .WillOnce(Return(true));
    EXPECT_CALL(_mockLib, png_image_finish_read(_, _, _, _, _))
        .WillOnce(DoAll(SetMessageOnPngImageArg<0>(_testErrorMessage.c_str()), Return(false)));
    EXPECT_THROW(
        try
        {
            PngImage image(_mockLib, _testFilename);
        }
        catch(const std::runtime_error& e)
        {
            EXPECT_THAT(e.what(), HasSubstr("finish"));
            EXPECT_THAT(e.what(), HasSubstr(_testErrorMessage));
            throw;
        },
        std::runtime_error);
}
