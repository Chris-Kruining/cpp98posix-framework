#include "Request.h"

namespace Communication
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

  std::string Request::GetMessage()
  {
    return this->message;
  }
}
