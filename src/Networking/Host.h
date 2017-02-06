#ifndef _NETWORKING_HOST_H_
#define _NETWORKING_HOST_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

namespace Networking
{
  struct Host : public sockaddr_in
  {
    std::string name;
    unsigned int port;
  };
}

#endif
