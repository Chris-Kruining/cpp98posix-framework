#include "Core/Application.h"
#include "UI/Console.h"
#include "Logging/TcpLogger.h"
#include "Networking/Tcp/Socket.h"

void Run(Core::Application* app)
{
  Networking::Host host;
  host.name = "127.0.0.1";
  host.port = 2000;
  Networking::Tcp::Socket socket(host);

  socket.Send("Hallo!");

  // TODO - draw menu and wait for input
  UI::Console::Write("Press any key to exit");
  UI::Console::WriteLine(UI::Console::Read());
}

int main(int argc, char* argv[])
{
  Core::Application app(argc, argv);
  return app.Run(Run);
}
