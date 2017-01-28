#include "ThreadManager.h"

namespace Threading
{
  vector<IThreadData*> ThreadManager::threads;

  void ThreadManager::JoinAll()
  {
    while(threads.size() > 0)
    {
      pthread_join(*threads[0]->thread, NULL);
    }
  }

  void ThreadManager::KillAll()
  {
    while(threads.size() > 0)
    {
      pthread_cancel(*threads[0]->thread);

      delete threads[0]->thread;

      threads.erase(threads.begin());
    }
  }
}
