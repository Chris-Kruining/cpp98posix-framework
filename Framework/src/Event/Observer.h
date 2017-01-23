#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include <iostream>
#include <string>

#include "IObserver.h"
#include "IObservable.h"
#include "EventArgs.h"

using namespace std;

namespace Event
{
  class Observer : public IObserver
  {
    private:
      IObservable* observable;
      string eventName;

    public:
      Observer(IObservable* observable, string eventName);
      virtual ~Observer();
      virtual void Update(IEventArgs* args) = 0;
      string GetEventName() const;

    protected:
      IObservable* GetObservable() const;
  };
}

#endif
