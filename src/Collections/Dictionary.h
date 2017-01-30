#ifndef _COLLECTIONS_DICTIONARY_H_
#define _COLLECTIONS_DICTIONARY_H_

#include <stdexcept>

#include "../Threading/Thread.h"

namespace Collections
{
  template <typename KeyT, typename ValueT>
  struct KeyValuePair
  {
    KeyT Key;
    ValueT Value;
  };

  template <typename KeyT, typename ValueT>
  class Dictionary : public Threading::Thread
  {
    private:
      int sizeIncrement;
      int size;
      KeyValuePair<KeyT, ValueT>* items;

      void Grow()
      {
        this->sizeIncrement *= 2;
        KeyValuePair<KeyT, ValueT>* newArr = new KeyValuePair<KeyT, ValueT>[this->sizeIncrement];

        std::copy(this->items, this->items + this->size, newArr);

        delete [] this->items;

        this->items = newArr;
      }

      void Shrink()
      {
        if(this->size >= this->sizeIncrement)
        {
          return;
        }

        this->sizeIncrement /= 2;
        KeyValuePair<KeyT, ValueT>* newArr = new KeyValuePair<KeyT, ValueT>[this->sizeIncrement];

        std::copy(this->items, this->items + this->size, newArr);

        delete [] this->items;

        this->items = newArr;
      }

    public:
      Dictionary()
      {
        this->sizeIncrement = 10;
        this->size = 0;
        this->items = new KeyValuePair<KeyT, ValueT>[10];

        this->Start();
      }
      virtual ~Dictionary()
      {
        delete [] this->items;
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

          if(this->size == this->sizeIncrement)
          {
            this->Grow();
          }
          else if(this->size < this->sizeIncrement / 2)
          {
            this->Shrink();
          }

          this->Unlock();
        }

        return NULL;
      }

      KeyValuePair<KeyT, ValueT> Get(KeyT key)
      {
        this->Lock();

        int index = 0; // TODO - get index by key

        if(index == -1)
        {
          this->Unlock();

          throw std::out_of_range(
            "KeyValuePair could not be found with this key"
          );
        }

        KeyValuePair<KeyT, ValueT> item = this->items[index];

        this->Unlock();

        return item;
      }

      int Add(KeyT key, ValueT value)
      {
        this->Lock();

        KeyValuePair<KeyT, ValueT> pair;
        pair.Key = key;
        pair.Value = value;

        this->items[this->size] = pair;
        this->size++;

        this->Signal();
        this->Unlock();

        return this->size - 1;
      }

      bool Remove(KeyT key)
      {
        this->Lock();

        // TODO - get index from key, delete KeyValuePair with that index, if not found return false

        // if(index < 0 || (index + count - 1) >= this->size)
        // {
        //   this->Unlock();
        //
        //   return false;
        // }
        //
        // this->size -= count;
        //
        // for(int i = index; i < this->size; i++)
        // {
        //   this->items[i] = this->items[i + count];
        // }
        //
        // this->Signal();
        this->Unlock();

        return true;
      }

      KeyValuePair<KeyT, ValueT> Shift()
      {
        this->Lock();

        while(this->size == 0)
        {
          this->Wait();
        }

        KeyValuePair<KeyT, ValueT> item = this->items[0];

        this->size--;

        for(int i = 0; i < this->size; i++)
        {
          this->items[i] = this->items[i + 1];
        }

        this->Signal();
        this->Unlock();

        return item;
      }

      KeyValuePair<KeyT, ValueT> Pop()
      {
        this->Lock();

        while(this->size == 0)
        {
          this->wait();
        }

        KeyValuePair<KeyT, ValueT> item = this->items[this->size - 1];
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

      Dictionary<KeyT, ValueT> Each(void (&m)(KeyT, ValueT))
      {
        this->Lock();

        for(int i = 0; i < this->size; i++)
        {
          m(this->items[i]->Key, this->items[i]->Value);
        }

        this->Unlock();

        return this;
      }
  };
}

#endif
