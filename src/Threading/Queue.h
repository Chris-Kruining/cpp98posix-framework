

#ifndef _THREADING_QUEUE_H_
#define _THREADING_QUEUE_H_

#include <vector>
#include <pthread.h>

#include "Mutex.h"
#include "Cond.h"

namespace Threading
{
  template <typename T>
  class Queue
  {
    protected:
      std::vector<T> items;
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

        while(this->items.size() == 0)
        {
          this->condition.Wait(this->mutex);
        }

        T item = this->items.front();
        this->items.erase(this->items.begin());

        this->mutex.Unlock();

        return item;
      }

      void Push(T item)
      {
        this->mutex.Lock();

        while(this->items.size() >= this->maxSize)
        {
          this->condition.Wait(this->mutex);
        }

        this->items.push_back(item);

        this->condition.Signal();
        this->mutex.Unlock();
      }

      int Size()
      {
        this->mutex.Lock();

        int size = this->items.size();

        this->mutex.Unlock();

        return size;
      }
  };
}

#endif
