#include "Thread.h"

namespace Threading
{
  Thread::Thread() : id(0), running(false), detached(false), stopped(false)
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

  bool Thread::Stop()
  {
    if(this->running && !this->stopped)
    {
      this->stopped = true;
      this->Detach();
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

  bool Thread::IsRunning() const
  {
    return this->running && !this->stopped;
  }

  void Thread::Wait()
  {
    if(!this->stopped)
    {
      this->condition.Wait(this->mutex);
    }
  }
  void Thread::Signal()
  {
    if(!this->stopped)
    {
      this->condition.Signal();
    }
  }

  void Thread::Lock()
  {
    if(!this->stopped)
    {
      this->mutex.Lock();
    }
  }
  void Thread::Unlock()
  {
    if(!this->stopped)
    {
      this->mutex.Unlock();
    }
  }

  void* Thread::RunThread(void* context)
  {
    return ((Thread*)context)->Run();
  }
}
