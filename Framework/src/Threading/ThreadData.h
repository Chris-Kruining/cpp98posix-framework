#ifndef _THREADING_THREADDATA_H_
#define _THREADING_THREADDATA_H_

#include <pthread.h>

namespace Threading
{
  struct IThreadData
  {
    public:
      pthread_t* thread;
      int id;
  };

  template <typename T, typename M, typename A>
  struct ThreadData : public IThreadData
  {
    public:
      T object;
      M method;
      A* args;
  };
}

#endif
