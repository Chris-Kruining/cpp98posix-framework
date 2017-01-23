#ifndef _COMMUNICATION_ISOCKET_H_
#define _COMMUNICATION_ISOCKET_H_

#include <string>

namespace Communication
{
  class ISocket
  {
    public:
      virtual bool Send(std::string message) = 0;
      virtual int Read(int method) = 0;
  };
}

#endif
