#ifndef _NETWORKING_TCP_EVENTARGS_H_
#define _NETWORKING_TCP_EVENTARGS_H_

#include <string>

#include "Event/EventArgs.h"

namespace Networking
{
  namespace Tcp
  {
    class EventArgs : public Event::EventArgs<std::string>
    {
      public:
        EventArgs(std::string message);
        virtual ~EventArgs();
        void SetMessage(std::string message);
        std::string GetMessage();
        void Copy(const EventArgs& base);
        std::string ToString() const;
    };
  }
}

#endif
