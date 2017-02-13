#ifndef _NETWORKING_TCP_LISTENER_H_
#define _NETWORKING_TCP_LISTENER_H_

#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

#include "Networking/Host.h"
#include "Networking/Tcp/Socket.h"
#include "Threading/Thread.h"
#include "Event/Observable.h"
#include "UI/Console.h"

namespace Networking
{
  namespace Tcp
  {
    class Listener : public Threading::Thread, public Event::Observable
    {
      private:
        int id;
        Collections::List<Networking::Tcp::Socket*> clients;
        Host host;
        socklen_t size;
        bool listening;

        int Bind();
        void Listen();

      public:
        Listener(Networking::Host host);
        virtual ~Listener();
        virtual void* Run();
    };
  }
}

#endif
