#ifndef _LOGGING_TCPLOGGER_H_
#define _LOGGING_TCPLOGGER_H_

#include "ILogger.h"
#include "LogEventArgs.h"
<<<<<<< develop
#include "../Event/Observer.h"
#include "../Event/EventHandler.h"
#include "../Communication/TcpSocket.h"
#include "../UI/Console.h"
=======
#include "Event/Observer.h"
#include "Event/EventHandler.h"
#include "Networking/Tcp/Socket.h"
#include "UI/Console.h"
>>>>>>> local

namespace Logging
{
  class TcpLogger : public ILogger
  {
    public:
      TcpLogger(Networking::Tcp::Socket* socket);
      ~TcpLogger();
      void OnUpdate(LogEventArgs* args);
      void Log(std::string);
  };
}

#endif
