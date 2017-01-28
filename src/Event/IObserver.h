#ifndef _IOBSERVER_H_
#define _IOBSERVER_H_

#include "IEventArgs.h"

namespace Event
{
  class IObservable; // put the include at the bottom to prevent an include loop

  class IObserver
  {
    public:
      virtual void Update(IEventArgs* args) = 0;
      virtual string GetEventName() const = 0;

    protected:
      virtual IObservable* GetObservable() const = 0;
  };
}

#include "IObservable.h"

#endif
