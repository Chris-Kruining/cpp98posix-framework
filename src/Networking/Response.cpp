#include "Response.h"

namespace Networking
{
  Response::Response(std::string message, Request request) : message(message), request(request)
  {

  }

  Response::~Response()
  {
    
  }
}
