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

  void* Console::Run()
  {
    while(this->IsRunning())
    {
      std::cout << this->messages.Shift();
    }

    return NULL;
  }
}
