#ifndef _COMMUNICATION_REQUEST_H_
#define _COMMUNICATION_REQUEST_H_

#include <string>

namespace Communication
{
  class Request
  {
    private:
      std::string message;

    public:
      Request(std::string message);
      virtual ~Request();
      void SetMessage(std::string message);
      std::string GetMessage();
      std::string ToString() const;
  };
}

#endif
