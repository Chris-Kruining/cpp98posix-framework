#include "TcpEventArgs.h"

namespace Communication
{
  TcpEventArgs::TcpEventArgs(string message) : EventArgs<string>(message)
  {

  }

  TcpEventArgs::~TcpEventArgs()
  {

  }

  void TcpEventArgs::SetMessage(string message)
  {
    this->value = message;
  }

  string TcpEventArgs::GetMessage()
  {
    return this->value;
  }

  void TcpEventArgs::Copy(const TcpEventArgs& base)
  {
    this->value = base.value;
  }

  string TcpEventArgs::ToString() const
  {
    return this->value;
  }
}
