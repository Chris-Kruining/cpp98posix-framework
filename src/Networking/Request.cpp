#include "Request.h"

namespace Networking
{
  Request::Request(std::string message) : message(message)
  {

  }

  Request::~Request()
  {

  }

  void Request::SetMessage(std::string message)
  {
    this->message = message;
  }

  std::string Request::GetMessage() const
  {
    return this->message;
  }
}
