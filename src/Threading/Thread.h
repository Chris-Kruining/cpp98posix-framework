#ifndef _THREADING_THREAD_H_
#define _THREADING_THREAD_H_

#include <pthread.h>

#include "IThread.h"

namespace Threading
{
  class Thread : public IThread
  {
    public:
      Thread();
      virtual ~Thread();

      bool Start();
      bool Join();
      bool Detach();

      void Wait();
      void Signal();

      void Lock();
      void Unlock();

      bool IsRunning();
      pthread_t Self();

      virtual void* Run() = 0;
      static void* RunThread(void* context);

    private:
      pthread_t id;
      pthread_mutex_t mutex;
      pthread_cond_t condition;
      bool running;
      bool detached;
  };
}

#endif