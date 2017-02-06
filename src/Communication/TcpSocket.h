#ifndef _COMMUNICATION_TCPSOCKET_H_
#define _COMMUNICATION_TCPSOCKET_H_

#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ISocket.h"
#include "TcpEventArgs.h"
#include "Logging/ILogger.h"
#include "Logging/LogEventArgs.h"
#include "Event/EventArgs.h"
#include "Event/Observable.h"
#include "Event/EventHandler.h"
#include "Threading/Queue.h"
#include "Threading/ThreadManager.h"

namespace Communication
{
  using namespace Logging;
  using namespace Event;
  using namespace std;

  struct AddressInfo
  {
    string ip;
    int port;
  };

  class TcpSocket : public ISocket, public Observable
  {
    private:
      bool isListening;
      bool connected;
      Threading::Queue<std::string> queue;
      void RunConnection(AddressInfo addressInfo);
      void RunListener(AddressInfo addressInfo);
      void HandleClient(int newsockfd);

    public:
      TcpSocket();
      virtual ~TcpSocket();
      void Listen(string ip, int port);
      void Connect(string ip, int port);
      bool Send(string message);
      int Read(int method);
      void Stop();
      void OnReceive(TcpEventArgs* args);
  };
}

#endif
