#ifndef _IOBSERVABLE_H_
#define _IOBSERVABLE_H_

#include <string>

#include "IObserver.h"
#include "EventArgs.h"

using std::string;

namespace Event
{
  class IObservable
  {
    public:
      virtual void Attach(IObserver* observer) = 0;
      virtual void Fire(string eventName, IEventArgs* args) = 0;
  };
}

#endif
