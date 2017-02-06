#include "TcpLogger.h"

namespace Logging
{
  TcpLogger::TcpLogger(Networking::Tcp::Socket* socket)
  {
    new Event::EventHandler<TcpLogger, LogEventArgs, &TcpLogger::OnUpdate>(this, socket, "tcp.log");
  }

  TcpLogger::~TcpLogger()
  {

  }

  void TcpLogger::OnUpdate(LogEventArgs* args)
  {
    this->Log(args->ToString());
  }

  void TcpLogger::Log(std::string message)
  {
    UI::Console::WriteLine(message);
  }
}
