#ifndef _THREADING_WORKER_H_
#define _THREADING_WORKER_H_

#include "IThread.h"
#include "Mutex.h"
#include "Cond.h"

namespace Threading
{
  template <typename C, void(C::*M)()>
  class Worker : public Thread
  {
    private:
      C* owner;

    public:
      Worker(){}
      Worker(C* owner) : owner(owner){}
      virtual ~Worker(){}

      void Start(C* owner)
      {
        this->owner = owner;

        Thread::Start();
      }

      void* Run()
      {
        while (this->IsRunning())
        {
          (this->owner->*M)();
        }

        return NULL;
      }
  };
}

#endif
