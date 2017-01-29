#include <unistd.h>

#include "Core/Application.h"
#include "UI/Console.h"

void Run(Core::Application* app)
{
  while(true)
  {
    if(UI::Console::Read() == "quit")
    {
      UI::Console::WriteLine("Time to exit");
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
