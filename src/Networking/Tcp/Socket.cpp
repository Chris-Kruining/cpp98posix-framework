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
      // delete this->sendWorker;
      // delete this->readWorker;
    }

    void Socket::Init()
    {
      new Event::EventHandler<Socket, EventArgs, &Socket::OnReceive>(this, this, "tcp.receive");

      this->sendWorker.Start(this);
      this->readWorker.Start(this);
    }

    void Socket::SendWorker()
    {
      while(this->sendWorker.IsRunning())
      {
        std::string message = this->sendQueue.Shift();

        if(message == "")
        {
          continue;
        }

        send(this->id, message.c_str(), message.size(), 0);
      }
    }

    void Socket::ReadWorker()
    {
      while(this->sendWorker.IsRunning())
      {
        int bufferSize = 1024;
        char buffer[bufferSize];

        recv(this->id, buffer, bufferSize, 0);

        readQueue.Push((new Networking::Response(std::string(buffer), Networking::Request(std::string(buffer)))));
      }
    }

    void Socket::Send(std::string message)
    {
      this->sendQueue.Push(message);
    }

    Networking::Response Socket::Read()
    {
      return *this->readQueue.Shift();
    }

    void Socket::OnReceive(EventArgs* args)
    {
      cout << args->ToString() << endl;
    }
  }
}
