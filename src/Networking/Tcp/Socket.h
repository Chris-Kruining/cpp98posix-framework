#ifndef _NETWORKING_TCP_SOCKET_H_
#define _NETWORKING_TCP_SOCKET_H_

#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "EventArgs.h"
#include "Networking/ISocket.h"
#include "Networking/Response.h"
#include "Networking/Host.h"
#include "Event/Observable.h"
#include "Event/EventHandler.h"
#include "Threading/Queue.h"
#include "Threading/Worker.h"
#include "UI/Console.h"

namespace Networking
{
  namespace Tcp
  {
    class Socket : public Event::Observable
    {

      public:
        Socket(Networking::Host host);
        Socket(int id); // when contructed in the listener
        virtual ~Socket();
        void Init();
        void SendWorker();
        void ReadWorker();
        void Send(std::string message);
        Networking::Response Read();
        void OnReceive(EventArgs* args);

      private:
        int id;
        Threading::Queue<std::string> sendQueue;
        Threading::Queue<Networking::Response*> readQueue;

        Threading::Worker<Socket, &Socket::SendWorker> sendWorker;
        Threading::Worker<Socket, &Socket::ReadWorker> readWorker;
    };
  }
}

#endif
