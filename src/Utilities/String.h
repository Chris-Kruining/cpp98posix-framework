#ifndef _UTILITIES_STRING_H_
#define _UTILITIES_STRING_H_

#include <sstream>
#include <string>
#include <vector>

namespace Utilities
{
  namespace String
  {
    std::vector<std::string> Split(std::string input, char token);
    bool Contains(std::vector<std::string> arr, std::string item);
    int ToInt(std::string str);
    std::string FromInt(int i);
  }
}

#endif
