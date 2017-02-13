#ifndef _THREADING_QUEUE_H_
#define _THREADING_QUEUE_H_

#include <pthread.h>

#include "Mutex.h"
#include "Cond.h"
#include "Collections/List.h"

namespace Threading
{
  template <typename T>
  class Queue
  {
    protected:
      Collections::List<T> items;
      Mutex mutex;
      Cond condition;
      static const int maxSize = 2000;

    public:
      Queue()
      {
      }

      virtual ~Queue()
      {
      }

      T Shift()
      {
        this->mutex.Lock();

        while(this->items.Size() == 0)
        {
          this->condition.Wait(this->mutex);
        }

        T item = this->items.Shift();

        this->mutex.Unlock();

        return item;
      }

      void Push(T item)
      {
        this->mutex.Lock();

        while(this->items.Size() >= this->maxSize)
        {
          this->condition.Wait(this->mutex);
        }

        this->items.Add(item);

        this->condition.Signal();
        this->mutex.Unlock();
      }

      int Size()
      {
        this->mutex.Lock();

        int size = this->items.Size();

        this->mutex.Unlock();

        return size;
      }
  };
}

#endif
