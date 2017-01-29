#include "Cond.h"

namespace Threading
{
  Cond::Cond()
  {
    pthread_cond_init(&this->id, NULL);
  }

  Cond::~Cond()
  {
    pthread_cond_destroy(&this->id);
  }

  int Cond::Wait(Mutex& mutex)
  {
    return pthread_cond_wait(&this->id, &mutex.id);
  }

  int Cond::Signal()
  {
    return pthread_cond_signal(&this->id);
  }
}
