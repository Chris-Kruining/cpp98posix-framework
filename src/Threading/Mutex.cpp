#include "Mutex.h"

namespace Threading
{
  Mutex::Mutex()
  {
    pthread_mutex_init(&this->id, NULL);
  }

  Mutex::~Mutex()
  {
    pthread_mutex_destroy(&this->id);
  }

  int Mutex::Lock()
  {
    return pthread_mutex_lock(&this->id);
  }

  int Mutex::Unlock()
  {
    return pthread_mutex_unlock(&this->id);
  }
}
