#include "Application.h"

namespace Core
{
  Application::Application(int argc, char* argv[])
  {
    this->ParseParams(argc, argv);
  }

  Application::~Application()
  {

  }

  int Application::Run(void(&m)(Application* app))
  {
    signal(SIGINT, &Kill);

    this->Init();

    m(this);

    return this->Stop();
  }

  void Application::Init()
  {
    UI::Console::WriteLine("Application is");
  }

  int Application::Stop()
  {
    Threading::ThreadManager::JoinAll();

    return 0;
  }

  void Application::Kill(int signalNumber)
  {
    UI::Console::WriteLine("Program killed with signal " + Utilities::String::FromInt(signalNumber));
    Threading::ThreadManager::KillAll();

    exit(0);
  }

  void Application::ParseParams(int argc, char* argv[])
  {
    UI::Console::WriteLine("Number of args :: " + Utilities::String::FromInt(argc -1));

    if(argc % 2 == 0)
    {
      return; // Cant make pair from an odd number of args(accounting for the 1 from the name of the program...)
    }

    for(int i = 1; i < argc; i += 2)
    {
      if(argv[i][0] != '-')
      {
        continue;
      }

      this->parameters.Add(argv[i], argv[i + 1]);
    }
  }

  Collections::Dictionary<std::string, std::string> Application::GetParameters()
  {
    return this->parameters;
  }
}
