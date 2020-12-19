#pragma once
#include <gmock/gmock.h>
#include <gtest/gtest.h>

MATCHER_P(DoublePtrStrEq, expectedStr, "") { return expectedStr == std::string(*arg); }

ACTION_TEMPLATE(FillArgPointeeBuffer, HAS_1_TEMPLATE_PARAMS(unsigned, argIndex), AND_2_VALUE_PARAMS(srcBuffer, srcSize))
{
    std::memcpy(std::get<argIndex>(args), srcBuffer, srcSize);
}

ACTION_TEMPLATE(SavePointerToArgReferee, HAS_1_TEMPLATE_PARAMS(unsigned, argIndex), AND_1_VALUE_PARAMS(pointer))
{
    *pointer = &(std::get<argIndex>(args));
}
