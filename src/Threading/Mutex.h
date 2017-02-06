#ifndef _THREADING_MUTEX_H_
#define _THREADING_MUTEX_H_

#include <pthread.h>

namespace Threading
{
  class Mutex
  {
    friend class Cond;

    private:
      pthread_mutex_t id;

    public:
      Mutex();
      virtual ~Mutex();

      int Lock();
      int Unlock();
  };
}

#endif
