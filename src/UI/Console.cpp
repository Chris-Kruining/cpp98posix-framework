#include "Console.h"

namespace UI
{
  Threading::Queue<std::string> Console::messages;

  Console::Console()
  {
    this->Start();
  }

  Console::~Console()
  {
    std::cout.flush();

    if(!this->Stop())
    {
      std::cout << "Console failed to detach" << '\n';
    }
  }

  void Console::Write(std::string message)
  {
    messages.Push(message);
  }

  void Console::WriteLine(std::string message)
  {
    Console::Write(message + '\n');
  }

  std::string Console::Read()
  {
    std::string input;
    std::cin >> input;

    return input;
  }

  char Console::ReadKey() // TODO - Make a proper key enum to cover non alfanumeric characters, or better, an enum based on current encoding
  {
    return std::cin.peek();
  }

  void* Console::Run()
  {
    while(this->IsRunning())
    {
      std::cout << this->messages.Shift();
    }

    return NULL;
  }
}
