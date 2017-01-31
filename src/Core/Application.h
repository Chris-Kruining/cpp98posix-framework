#ifndef _CORE_APPLICATION_H_
#define _CORE_APPLICATION_H_

#include <signal.h>
#include <string>

#include "Utilities/String.h"
#include "Collections/Dictionary.h"
#include "UI/Console.h"
#include "Threading/ThreadManager.h"

namespace Core
{
  class Application
  {
    private:
      Collections::Dictionary<std::string, std::string> parameters;
      UI::Console console;

    public:
      Application(int argc, char* argv[]);
      ~Application();

      int Run(void(&m)(Application* app));
      void Init();
      int Stop();
      void ParseParams(int argc, char* argv[]);
      Collections::Dictionary<std::string, std::string> GetParameters();
      static void Kill(int signalNumber);
  };
}

#endif
