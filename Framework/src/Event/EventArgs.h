#ifndef _EVENTARGS_H_
#define _EVENTARGS_H_

#include <string>

#include "IEventArgs.h"

namespace Event
{
  using std::string;

  template <typename T>
  class EventArgs : public IEventArgs
  {
    protected:
      T value;

    public:
      EventArgs(T value) : value(value)
      {

      }

      ~EventArgs()
      {

      }

      EventArgs<T> operator=(const EventArgs<T>& base)
      {
        if(this == &base)
        {
          return *this;
        }

        this->Copy(base);
        return *this;
      }

      virtual void Copy(const EventArgs<T>& base)
      {
        this->value = base.value;
      }

      virtual string ToString() const
      {
        return "";
      }

      void SetValue(T value)
      {
        this->value = value;
      }

      T GetValue() const
      {
        return this->value;
      }
  };
}

#endif
