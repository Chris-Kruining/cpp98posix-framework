#include "Core/Application.h"
#include "UI/Console.h"
#include "Networking/Tcp/Listener.h"
#include "Networking/Host.h"

void Run(Core::Application* app)
{
  Networking::Host host;
  host.name = "";
  host.port = 2000;
  Networking::Tcp::Listener listener(host);

  // TODO - draw menu and wait for input
  UI::Console::Write("Press any key to exit");
  UI::Console::WriteLine(UI::Console::Read());
}

int main(int argc, char* argv[])
{
  Core::Application app(argc, argv);

  return app.Run(Run);
}
