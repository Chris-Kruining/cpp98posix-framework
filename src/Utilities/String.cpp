#include "String.h"

#include <iostream>

namespace Utilities
{
  namespace String
  {
    std::vector<std::string> Split(std::string str, char token)
    {
      std::vector<std::string> list;
      list.push_back("");
      int index = 0;

      for(unsigned int i = 0; i < str.length(); i++)
      {
        if(str[i] == token)
        {
          list.push_back("");
          index++;
        }
        else
        {
          list[index] += str[i];
        }
      }

      return list;
    }

    bool Contains(std::vector<std::string> arr, std::string item)
    {
      for(unsigned int i = 0; i < arr.size(); i++)
      {
        if(arr[i].compare(item) == 0)
        {
          return true;
        }
      }

      return false;
    }

    int ToInt(std::string str)
    {
      int out = 0;
      bool found = false;

      for(unsigned int i = 0; i < str.length(); i++)
      {
        if(str[i] >= 48 && str[i] <= 57)
        {
          out = (out * 10) + (((int)str[i]) - 48);
          found = true;
          continue;
        }

        if(found)
        {
          break;
        }
      }

      return out;
    }

    std::string FromInt(int i)
    {
      std::string str;

      // converting base 10
      while (i > 0)
      {
        str = (char) ((i % 10) + 48) + str;
        i /= 10;
      }

      return str;
    }
  }
}
