#ifndef _NETWORKING_REQUEST_H_
#define _NETWORKING_REQUEST_H_

#include <string>

namespace Networking
{
  class Request
  {
    private:
      std::string message;

    public:
      Request(std::string message);
      virtual ~Request();
      void SetMessage(std::string message);
      std::string GetMessage() const;
      std::string ToString() const;
  };
}

#endif
