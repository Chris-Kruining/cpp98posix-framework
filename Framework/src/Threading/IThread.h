#ifndef _THREADING_ITHREAD_H_
#define _THREADING_ITHREAD_H_

namespace Threading
{
  class IThread
  {
    public:
      virtual void* Run() = 0;
  };
}

#endif
