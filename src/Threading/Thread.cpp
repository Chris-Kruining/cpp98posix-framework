#include "Thread.h"

namespace Threading
{
  Thread::Thread()
  {
    this->id = 0;
    this->lockedThreads = new pthread_t[256];
    this->lockedThreadsCount = 0;
    this->running = false;
    this->detached = false;
    this->stopped = false;
  }

  Thread::~Thread()
  {
    this->stopped = true;

    if(!this->detached && this->running)
    {
      pthread_detach(this->id);
    }

    if(this->running)
    {
      pthread_cancel(this->id);
    }

    delete [] this->lockedThreads;
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
  bool Thread::IsLocked()
  {
    for(unsigned char i = 0; i < this->lockedThreadsCount; i++)
    {
      if(this->lockedThreads[i] == this->Self())
      {
        return true;
      }
    }

    return false;
  }
  bool Thread::CanLock()
  {
    return !this->IsLocked() && this->lockedThreadsCount < 256;
  }
  pthread_t Thread::Self()
  {
    return pthread_self();
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
    if(!this->stopped && this->CanLock())
    {
      this->mutex.Lock();

      this->lockedThreads[this->lockedThreadsCount] = this->Self();
      this->lockedThreadsCount++;
    }
  }
  void Thread::Unlock()
  {
    if(!this->stopped && this->IsLocked())
    {
      this->mutex.Unlock();

      bool found = false;
      for(unsigned char i = 0; i < this->lockedThreadsCount; i++)
      {
        if(this->lockedThreads[i] == this->Self())
        {
          found = true;
        }

        if(found)
        {
          this->lockedThreads[i] = this->lockedThreads[i + 1];
        }
      }
    }
  }

  void* Thread::RunThread(void* context)
  {
    return ((Thread*)context)->Run();
  }
}
