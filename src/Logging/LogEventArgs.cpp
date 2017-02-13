#include "LogEventArgs.h"

namespace Logging
{
  LogEventArgs::LogEventArgs() : EventArgs<string>(""), level(Info)
  {

  }

  LogEventArgs::LogEventArgs(const LogEventArgs &logEventArgs) : EventArgs<string>(logEventArgs.value)
  {
    this->level = logEventArgs.level;
  }

  void LogEventArgs::Copy(const LogEventArgs& base)
  {
    this->value = base.value;
    this->level = base.level;
  }

  LogEventArgs::~LogEventArgs()
  {

  }

  string LogEventArgs::ToString() const
  {
    return this->value;
  }

  void LogEventArgs::SetMessage(string message)
  {
    this->value = message;
  }

  string LogEventArgs::GetMessage()
  {
    return this->value;
  }

  void LogEventArgs::SetLevel(Logging::LogLevel level)
  {
    this->level = level;
  }

  Logging::LogLevel LogEventArgs::GetLevel()
  {
    return this->level;
  }
}
