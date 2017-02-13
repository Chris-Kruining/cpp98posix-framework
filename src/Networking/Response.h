#ifndef _NETWORKING_RESPONSE_H_
#define _NETWORKING_RESPONSE_H_

#include <string>

#include "Request.h"

namespace Networking
{
  class Response
  {
    private:
      std::string message;
      Request request;

    public:
      Response(std::string message, Request Request);
      virtual ~Response();
  };
}

#endif
