#ifndef _UI_CONSOLE_H_
#define _UI_CONSOLE_H_

#include <iostream>
#include <string>

#include "Threading/Queue.h"
#include "Threading/Thread.h"

namespace UI
{
  class Console : public Threading::Thread
  {
    private:
      static Threading::Queue<std::string> messages;

    public:
      Console();
      virtual ~Console();

      static void Write(std::string message);
      static void WriteLine(std::string message);
      static std::string Read();
      static char ReadKey();

      virtual void* Run(); // inherited from Thread
  };
}

#endif
