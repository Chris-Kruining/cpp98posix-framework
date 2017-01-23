#ifndef _LOGGING_ILOGGER_H_
#define _LOGGING_ILOGGER_H_

#include <string>

namespace Logging
{
  using std::string;

  enum LogLevel
  {
    Error,
    Warning,
    Debug,
    Info
  };

  class ILogger
  {
    public:
      virtual void Log(string message) = 0;
  };
}

#endif
