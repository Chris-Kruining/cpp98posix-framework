

#ifndef _THREADING_QUEUE_H_
#define _THREADING_QUEUE_H_

#include <vector>
#include <pthread.h>

namespace Threading
{
  template <typename T>
  class Queue
  {
    protected:
      std::vector<T> items;
      pthread_mutex_t mutex;
      pthread_cond_t condition;
      static const int maxSize = 2000;

    public:
      Queue()
      {
        pthread_mutex_init(&this->mutex, NULL);
        pthread_cond_init(&this->condition, NULL);
      }

      virtual ~Queue()
      {
        pthread_mutex_destroy(&this->mutex);
        pthread_cond_destroy(&this->condition);
      }

      T Shift()
      {
        pthread_mutex_lock(&this->mutex);

        while(this->items.size() == 0)
        {
          pthread_cond_wait(&this->condition, &this->mutex);
        }

        T item = this->items.front();
        this->items.erase(this->items.begin());

        pthread_mutex_unlock(&this->mutex);

        return item;
      }

      void Push(T item)
      {
        pthread_mutex_lock(&this->mutex);

        while(this->items.size() >= this->maxSize)
        {
          pthread_cond_wait(&this->condition, &this->mutex);
        }

        this->items.push_back(item);

        pthread_cond_signal(&this->condition);
        pthread_mutex_unlock(&this->mutex);
      }

      int Size()
      {
        pthread_mutex_lock(&this->mutex);

        int size = this->items.size();

        pthread_mutex_unlock(&this->mutex);

        return size;
      }
  };
}

#endif
