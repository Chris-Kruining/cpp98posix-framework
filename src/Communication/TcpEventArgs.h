#ifndef _COMMUNICATION_TCPEVENTARGS_H_
#define _COMMUNICATION_TCPEVENTARGS_H_

#include <string>

#include "../Event/EventArgs.h"

namespace Communication
{
  using namespace Event;
  using namespace std;

  class TcpEventArgs : public EventArgs<string>
  {
    public:
      TcpEventArgs(string message);
      virtual ~TcpEventArgs();
      void SetMessage(string message);
      string GetMessage();
      void Copy(const TcpEventArgs& base);
      string ToString() const;
  };
}

#endif
