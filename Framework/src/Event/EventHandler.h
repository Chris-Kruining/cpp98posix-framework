#ifndef _EVENTEVENTHANDLER_H_
#define _EVENTEVENTHANDLER_H_

#include <string>

#include "Observer.h"

namespace Event
{
  using std::string;

  template <typename O, typename T, void (O::*M)(T*)>
  class EventHandler : public Observer
  {
    private:
      O* observer;

    public:
      EventHandler(O* observer, IObservable* observable, string eventName) : Observer(observable, eventName), observer(observer)
      {

      }

      virtual ~EventHandler()
      {
      }

      void Update(IEventArgs* args)
      {
        (observer->*M)(static_cast<T*>(args));
      }
  };
}

#endif
