#ifndef _EVENT_OBSERVABLE_H_
#define _EVENT_OBSERVABLE_H_

#include <vector>
#include <string>
#include <iostream>
#include <unistd.h>

#include "IObservable.h"
#include "IObserver.h"
#include "EventArgs.h"
<<<<<<< develop
#include "../Utilities/String.h"
#include "../Threading/ThreadManager.h"
=======
#include "Utilities/String.h"
>>>>>>> local

using namespace std;
using namespace Utilities;

namespace Event
{
  class Observable : public IObservable
  {
    private:
      vector<class IObserver*> observers;
      bool IsInNamespace(IObserver* observer, string eventName);

    public:
      Observable();
      virtual ~Observable();
      void Attach(IObserver* observer);
      void Fire(string eventName, IEventArgs* args);
  };
}

#endif
