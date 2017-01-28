#include "String.h"

namespace Utilities
{
  namespace String
  {
    std::vector<string> Split(string input, char token)
    {
      stringstream stream;
      string segment;
      vector<std::string> seglist;

      stream << input;

      while(getline(stream, segment, token))
      {
         seglist.push_back(segment);
      }

      return seglist;
    }

    bool Contains(vector<string> arr, string item)
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

    unsigned int ToInt(const string str, int h)
    {
        return !str[h]
          ? 5381
          : (ToInt(str, h+1) * 33) ^ str[h];
    }
  }
}
