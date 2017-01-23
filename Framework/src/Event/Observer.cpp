#include "Observer.h"

namespace Event
{
  Observer::Observer(IObservable* observable, string eventName) : observable(observable), eventName(eventName)
  {
    this->observable->Attach(this);
  }

  Observer::~Observer()
  {
  }

  IObservable* Observer::GetObservable() const
  {
    return this->observable;
  }

  string Observer::GetEventName() const
  {
    return this->eventName;
  }
}
