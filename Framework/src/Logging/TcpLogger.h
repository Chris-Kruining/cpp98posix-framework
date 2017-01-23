#ifndef _LOGGING_TCPLOGGER_H_
#define _LOGGING_TCPLOGGER_H_

#include "ILogger.h"
#include "LogEventArgs.h"
#include "../Event/Observer.h"
#include "../Event/EventHandler.h"
#include "../Communication/TcpSocket.h"
#include "../UI/Console.h"

namespace Logging
{
  using namespace Event;
  using Communication::TcpSocket;

  class TcpLogger : public ILogger
  {
    public:
      TcpLogger(TcpSocket* socket);
      ~TcpLogger();
      void OnUpdate(LogEventArgs* args);
      void Log(string);
  };
}

#endif
