#include "Core/Application.h"
#include "UI/Console.h"
#include "Communication/TcpSocket.h"
#include "Logging/TcpLogger.h"

void Run(Core::Application* app)
{
    Communication::TcpSocket socket;
    Logging::TcpLogger logger(&socket);

    socket.Listen("0.0.0.0", 2000);

    // TODO - draw menu and wait for input
    UI::Console::Write("What to read, what to read: ");
    UI::Console::WriteLine(UI::Console::Read());
}

int main(int argc, char* argv[])
{
  Core::Application app(argc, argv);
  return app.Run(Run);
}
