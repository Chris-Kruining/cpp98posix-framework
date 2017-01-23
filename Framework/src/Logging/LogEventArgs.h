#ifndef _LOGEVENTARGS_H_
#define _LOGEVENTARGS_H_

#include <string>

#include "../Event/EventArgs.h"
#include "ILogger.h"

namespace Logging
{
  using namespace Event;
  using namespace std;

  class LogEventArgs : public EventArgs<string>
  {
    private:
      Logging::LogLevel level;

    public:
      // basic constructor and deconstructor
      LogEventArgs();
      virtual ~LogEventArgs();

      // for deep copying
      LogEventArgs(const LogEventArgs& logEventArgs);
      void Copy(const LogEventArgs& base);

      // converting to string
      string ToString() const;

      void SetMessage(string message);
      string GetMessage();

      void SetLevel(Logging::LogLevel level);
      Logging::LogLevel GetLevel();
  };
}

#endif
