#include <unistd.h>
#include <string>

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

  while(true)
  {
    if(UI::Console::Read() == "quit")
    {
      return;
    }

    UI::Console::WriteLine("I'm up for another round");
  }
}

int main(int argc, char* argv[])
{
  Core::Application app(argc, argv);

  return app.Run(Run);
}
