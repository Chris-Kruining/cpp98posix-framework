#include "../../src/Utilities/String.cpp"

#include <iostream>

TEST(Utilities_String_Split, Basic)
{
  std::vector<std::string> v;
  v.push_back("a");
  v.push_back("beautiful");
  v.push_back("string");
  v.push_back("vector");

  EXPECT_EQ(v, Utilities::String::Split("a-beautiful-string-vector", '-'));
}

TEST(Utilities_String_Contains, Basic)
{
  std::vector<std::string> v;
  v.push_back("a");
  v.push_back("beautiful");
  v.push_back("string");
  v.push_back("vector");

  EXPECT_TRUE(Utilities::String::Contains(v, "string"));
  EXPECT_FALSE(Utilities::String::Contains(v, "false"));
}

TEST(Utilities_String_ToInt, CleanString)
{
  std::cout << Utilities::String::ToInt("123456") << '\n';

  EXPECT_EQ(123456, Utilities::String::ToInt("123456"));
}

TEST(Utilities_String_ToInt, PrefixedAndSuffixedString)
{
  EXPECT_EQ(123456, Utilities::String::ToInt("prefix_123456_suffix"));
}

TEST(Utilities_String_FromInt, Basic)
{
  EXPECT_EQ("123456", Utilities::String::FromInt(123456));
}
