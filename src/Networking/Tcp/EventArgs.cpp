#include "EventArgs.h"

namespace Networking
{
  namespace Tcp
  {
    EventArgs::EventArgs(std::string message) : Event::EventArgs<std::string>(message)
    {

    }

    EventArgs::~EventArgs()
    {

    }

    void EventArgs::SetMessage(std::string message)
    {
      this->value = message;
    }

    std::string EventArgs::GetMessage()
    {
      return this->value;
    }

    void EventArgs::Copy(const EventArgs& base)
    {
      this->value = base.value;
    }

    std::string EventArgs::ToString() const
    {
      return this->value;
    }
  }
}
