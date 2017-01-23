#ifndef _IEVENTARGS_H_
#define _IEVENTARGS_H_

#include <string>

namespace Event
{
  using namespace std;

  class IEventArgs
  {
    public:
      virtual string ToString() const = 0;

    protected:
  };
}

#endif
