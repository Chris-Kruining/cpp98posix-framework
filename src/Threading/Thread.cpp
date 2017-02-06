#include "Thread.h"

namespace Threading
{
  Thread::Thread() : id(0), running(false), detached(false), stopped(false)
  {
    pthread_mutex_init(&this->mutex, NULL);
    pthread_cond_init(&this->condition, NULL);
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

    pthread_mutex_destroy(&this->mutex);
    pthread_cond_destroy(&this->condition);
  }

  bool Thread::Start()
  {
    if(!this->running)
    {
      if(pthread_create(&this->id, NULL, RunThread, this) == 0)
      {
        this->running = true;
        return true;
      }
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
    if(this->running)
    {
      if(pthread_join(this->id, NULL) == 0)
      {
        this->detached = true;
        this->running = false;
        return true;
      }
    }

    return false;
  }

  bool Thread::Detach()
  {
    if(this->running && !this->detached)
    {
      if(pthread_detach(this->id) == 0)
      {
        this->detached = true;
        return true;
      }
    }

    return false;
  }

  bool Thread::IsRunning() const
  {
    return this->running && !this->stopped;
  }

  void Thread::Wait()
  {
    pthread_cond_wait(&this->condition, &this->mutex);
  }
  void Thread::Signal()
  {
    pthread_cond_signal(&this->condition);
  }

  void Thread::Lock()
  {
    pthread_mutex_lock(&this->mutex);
  }
  void Thread::Unlock()
  {
    pthread_mutex_unlock(&this->mutex);
  }

  void* Thread::RunThread(void* context)
  {
    return ((Thread*)context)->Run();
  }
}
