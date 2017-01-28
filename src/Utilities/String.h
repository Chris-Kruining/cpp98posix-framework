#ifndef _UTILITIES_STRING_H_
#define _UTILITIES_STRING_H_

#include <sstream>
#include <string>
#include <vector>

using namespace std;

namespace Utilities
{
  namespace String
  {
    std::vector<string> Split(string input, char token);
    bool Contains(vector<string> arr, string item);
    unsigned int ToInt(const char* str, int h = 0);
  }
}

#endif
