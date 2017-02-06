#include "catch.hpp"
#include "../../src/Utilities/String.cpp"

TEST_CASE("Basic", "[Utilities_String_Split]")
{
  std::vector<std::string> v;
  v.push_back("a");
  v.push_back("beautiful");
  v.push_back("string");
  v.push_back("vector");

  REQUIRE(v == Utilities::String::Split("a-beautiful-string-vector", '-'));
}

TEST_CASE("Basic", "[Utilities_String_Contains]")
{
  std::vector<std::string> v;
  v.push_back("a");
  v.push_back("beautiful");
  v.push_back("string");
  v.push_back("vector");

  REQUIRE(Utilities::String::Contains(v, "string"));
  REQUIRE(!Utilities::String::Contains(v, "false"));
}

TEST_CASE("CleanString", "[Utilities_String_ToInt]")
{
  REQUIRE(123456 == Utilities::String::ToInt("123456"));
}

TEST_CASE("PrefixedAndSuffixedString", "[Utilities_String_ToInt]")
{
  REQUIRE(123456 == Utilities::String::ToInt("prefix_123456_suffix"));
}

TEST_CASE("Basic", "[Utilities_String_FromInt]")
{
  REQUIRE("123456" == Utilities::String::FromInt(123456));
}
