#ifndef _THREADING_THREADMANAGER_H_
#define _THREADING_THREADMANAGER_H_

#include <vector>
#include <pthread.h>

#include "ThreadData.h"

using namespace std;

namespace Threading
{
  class ThreadManager
  {
    private:
      ThreadManager(){}

      static vector<IThreadData*> threads;

      template <typename T, typename M, typename D> static void* ThreadStart(void* context)
      {
        ThreadData<T, M, D>* thread = (ThreadData<T, M, D>*)context;

        (thread->object->*thread->method)(*thread->args);

        // Thread is finished, so we delete it
        // TODO - export this to seperate function with queue
        int index = -1;

        for(unsigned int i = 0; i < threads.size(); i++)
        {
          if(threads[i]->id == thread->id)
          {
            index = i;
          }
        }

        if(index != -1)
        {
          delete threads[index]->thread;
          threads.erase(threads.begin() + index);
        }

        pthread_exit(NULL);
      }

    public:
      static void JoinAll();
      static void KillAll();

      template <typename T, typename M, typename D> static int SpawnThread(T obj, M method, D data)
      {
        ThreadData<T, M, D>* thread = new ThreadData<T, M, D>;
        thread->thread = new pthread_t();
        thread->object = obj;
        thread->method = method;
        thread->args = new D(data);

        int result = pthread_create(thread->thread, NULL, &ThreadManager::ThreadStart<T, M, D>, thread);

        if(result)
        {
          return -1;
        }
        else
        {
          threads.push_back(thread);
          thread->id = threads.size() - 1;

          return thread->id;
        }
      }
  };
}

#endif
