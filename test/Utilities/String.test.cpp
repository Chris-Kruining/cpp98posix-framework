#include "../../src/Utilities/String.cpp"

TEST(Utilities_String, FromInt)
{
    EXPECT_EQ("123456", Utilities::String::FromInt(123456));
}
