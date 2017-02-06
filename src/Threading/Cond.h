#ifndef _THREADING_COND_H_
#define _THREADING_COND_H_

#include <pthread.h>

#include "Mutex.h"

namespace Threading
{
  class Cond
  {
    private:
      pthread_cond_t id;

    public:
      Cond();
      virtual ~Cond();

      int Wait(Mutex& mutex);
      int Signal();
  };
}

#endif
