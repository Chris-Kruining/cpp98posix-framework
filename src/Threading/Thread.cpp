#include "Thread.h"

namespace Threading
{
  Thread::Thread() : id(0), running(false), detached(false)
  {
  }

  Thread::~Thread()
  {
    if(!this->detached && this->running)
    {
      pthread_detach(this->id);
    }

    if(this->running)
    {
      pthread_cancel(this->id);
    }
  }

  bool Thread::Start()
  {
    if(!this->running && pthread_create(&this->id, NULL, RunThread, this) == 0)
    {
      this->running = true;
      return true;
    }

    return false;
  }

  bool Thread::Join()
  {
    if(this->running && pthread_join(this->id, NULL) == 0)
    {
      this->detached = true;
      this->running = false;
      return true;
    }

    return false;
  }

  bool Thread::Detach()
  {
    if(this->running && !this->detached && pthread_detach(this->id) == 0)
    {
      this->detached = true;
      return true;
    }

    return false;
  }

  bool Thread::IsRunning()
  {
    return this->running;
  }

  void Thread::Wait()
  {
    this->condition.Wait(this->mutex);
  }
  void Thread::Signal()
  {
    this->condition.Signal();
  }

  void Thread::Lock()
  {
    this->mutex.Lock();
  }
  void Thread::Unlock()
  {
    this->mutex.Unlock();
  }

  void* Thread::RunThread(void* context)
  {
    return ((Thread*)context)->Run();
  }
}
