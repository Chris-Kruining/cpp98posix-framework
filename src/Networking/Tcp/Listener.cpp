#include "Listener.h"

namespace Networking
{
  namespace Tcp
  {
    Listener::Listener(Networking::Host host)
    {
      this->id = socket(AF_INET, SOCK_STREAM, 0);

      if(this->id < 0)
      {
        return;
      }

      this->listening = false;

      this->host = host;
      this->host.sin_family = AF_INET;
      // this->host.sin_addr.s_addr = htons(this->host.name); TODO - fix this
      this->host.sin_addr.s_addr = htons(INADDR_ANY);
      this->host.sin_port = htons(this->host.port);

      if(this->Bind() < 0)
      {
        return;
      }

      this->size = sizeof((sockaddr_in)this->host);

      this->Listen();

      this->Start();
    }

    Listener::~Listener()
    {
      this->listening = false;

      this->Stop();

      close(this->id);
    }

    void Listener::Listen()
    {
      if(!this->listening)
      {
        listen(this->id, 1);
        this->listening = true;
      }
    }

    int Listener::Bind()
    {
      return bind(this->id, (struct sockaddr*)&this->host, sizeof(this->host));
    }

    void* Listener::Run()
    {
      while (this->listening)
      {
        UI::Console::WriteLine("waiting for a client :D");

        int client = accept(this->id, (struct sockaddr*)&this->host, &this->size);

        if(client < 0)
        {
          continue;
        }

        this->clients.Add(new Networking::Tcp::Socket(client));

        // TODO - come up with a mechanism to remove clients who are no longer connected
      }

      return NULL;
    }
  }
}
