#ifndef _NETWORKING_ISOCKET_H_
#define _NETWORKING_ISOCKET_H_

#include <string>

namespace Networking
{
  class ISocket
  {
    public:
      virtual bool Send(std::string message) = 0;
      virtual int Read(int method) = 0;
  };
}

#endif
