#ifndef _COLLECTIONS_LIST_H_
#define _COLLECTIONS_LIST_H_

#include <stdexcept>

#include "Threading/Thread.h"

namespace Collections
{
  template <typename T>
  class List : public Threading::Thread
  {
    private:
      int capacity;
      int size;
      int position;
      T* items;

      void Grow()
      {
        this->capacity *= 2;
        T* newArr = new T[this->capacity];

        std::copy(this->items, this->items + this->size, newArr);

        delete [] this->items;

        this->items = newArr;

        this->Signal();
      }

      void Shrink()
      {
        if(this->size >= (this->capacity / 2))
        {
          return;
        }

        this->capacity /= 2;
        T* newArr = new T[this->capacity];

        std::copy(this->items, this->items + this->size, newArr);

        delete [] this->items;

        this->items = newArr;

        this->Signal();
      }

    public:
      List()
      {
        this->capacity = 2;
        this->size = 0;
        this->position = 0;
        this->items = new T[2];

        this->Start();
      }
      virtual ~List()
      {
        this->Lock();

        delete [] this->items;

        this->Unlock();
      }

      virtual void* Run() // inherited from Thread
      {
        int lastSize = 0;

        while(this->IsRunning()) // administration backgroundworker
        {
          this->Lock();

          while(this->size == lastSize)
          {
            this->Wait();
          }

          lastSize = this->size;

          if(this->size == this->capacity)
          {
            this->Grow();
          }
          else if(this->size < this->capacity / 2)
          {
            this->Shrink();
          }

          this->Unlock();
          // Find a way to do background management like growing in here
        }

        return NULL;
      }

      T Get(int index)
      {
        this->Lock();

        if(index < 0 || index >= this->size)
        {
          this->Unlock();

          throw std::out_of_range(
            "Index is out of bounds"
          );
        }

        T item = this->items[index];

        this->Unlock();

        return item;
      }

      int Add(T item)
      {
        this->Lock();

        if(this->size == this->capacity)
        {
          this->Grow();
        }

        this->items[this->size] = item;
        this->size++;

        this->Signal();
        this->Unlock();

        return this->size - 1;
      }

      bool Remove(int index, int count = 1)
      {
        this->Lock();

        if(index < 0 || (index + count - 1) >= this->size)
        {
          this->Unlock();

          return false;
        }

        this->size -= count;

        for(int i = index; i < this->size; i++)
        {
          this->items[i] = this->items[i + count];
        }

        this->Signal();
        this->Unlock();

        return true;
      }

      T Shift(bool block = true)
      {
        this->Lock();

        while(this->size == 0)
        {
          this->Wait();
        }

        T item = this->items[0];

        this->size--;

        for(int i = 0; i < this->size; i++)
        {
          this->items[i] = this->items[i + 1];
        }

        this->Signal();
        this->Unlock();

        return item;
      }

      T Pop(bool block = true)
      {
        this->Lock();

        if(block)
        {
          while(this->size == 0)
          {
            this->wait();
          }
        }
        else if(!block && this->size == 0)
        {
          this->Unlock();

          return NULL;
        }

        T item = this->items[this->size - 1];
        delete this->items[this->size - 1];

        this->size--;

        this->Signal();
        this->Unlock();

        return item;
      }

      int Size()
      {
        this->Lock();

        int size = this->size;

        this->Unlock();

        return size;
      }

      List<T>* Each(void (*m)(T))
      {
        this->Lock();

        for(int i = 0; i < this->size; i++)
        {
          m(this->items[i]);
        }

        this->Unlock();

        return this;
      }
  };
}

#endif
