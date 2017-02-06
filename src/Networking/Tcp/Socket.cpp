#include "Socket.h"

#include <iostream>
#include <csignal>
#include <unistd.h>

namespace Networking
{
  namespace Tcp
  {
    Socket::Socket(Networking::Host host) : id(0)
    {
      this->Init();
    }

    Socket::Socket(int id) : id(id)
    {
      this->Init();
    }

    Socket::~Socket()
    {

    }

    void Socket::Init()
    {
      signal(SIGPIPE, SIG_IGN);
      new Event::EventHandler<Socket, EventArgs, &Socket::OnReceive>(this, this, "tcp.receive");
    }

    void* Socket::Run()
    {
      return NULL;
    }

    void Socket::Send(std::string message)
    {
      this->sendQueue.Push(message);
    }

    Networking::Response Socket::Read()
    {
      return this->readQueue.Shift();
    }

    void Socket::OnReceive(EventArgs* args)
    {
      cout << args->ToString() << endl;
    }
  }
}
