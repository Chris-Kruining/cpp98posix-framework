#include "TcpLogger.h"

namespace Logging
{
  TcpLogger::TcpLogger(TcpSocket* socket)
  {
    new EventHandler<TcpLogger, LogEventArgs, &TcpLogger::OnUpdate>(this, socket, "tcp.log");
  }

  TcpLogger::~TcpLogger()
  {

  }

  void TcpLogger::OnUpdate(LogEventArgs* args)
  {
    this->Log(args->ToString());
  }

  void TcpLogger::Log(string message)
  {
    UI::Console::WriteLine(message);
  }
}
