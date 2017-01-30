#include <unistd.h>
#include <string>

#include "Core/Application.h"
#include "UI/Console.h"
#include "Collections/List.h"

void Run(Core::Application* app)
{
  Collections::List<std::string> list;
  list.Add("Kaas");
  list.Add("is");
  list.Add("lekker");
  list.Add("!!!");

  while(true)
  {
    list.Each([](std::string item){
      UI::Console::WriteLine(item);
    });

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
