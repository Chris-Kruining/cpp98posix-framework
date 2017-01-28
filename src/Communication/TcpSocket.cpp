#include "TcpSocket.h"

#include <iostream>
#include <csignal>
#include <unistd.h>

using namespace std;

#define BUFFERSIZE 2048

namespace Communication
{
  TcpSocket::TcpSocket() : isListening(false), connected(false)
  {
    signal(SIGPIPE, SIG_IGN);
    new EventHandler<TcpSocket, TcpEventArgs, &TcpSocket::OnReceive>(this, this, "tcp.receive");
  }

  TcpSocket::~TcpSocket()
  {

  }

  void TcpSocket::Connect(string ip, int port)
  {
    AddressInfo addressInfo;
    addressInfo.ip = ip;
    addressInfo.port = port;

    Threading::ThreadManager::SpawnThread(this, &TcpSocket::RunConnection, addressInfo);
  }

  void TcpSocket::RunConnection(AddressInfo addressInfo)
  {
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[BUFFERSIZE];
    std::string input;

    portno = addressInfo.port;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
      cout << "ERROR opening socket" << endl;
      return;
    }

    server = gethostbyname(addressInfo.ip.c_str());

    if(server == NULL)
    {
      cout << "ERROR, no such host" << endl;
      return;
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;

    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
    {
      cout << "ERROR connecting" << endl;
      return;
    }

    this->connected = true;
    while(this->connected)
    {
      input = this->queue.Shift();

      cout << "sending :: " << input << endl;

      if(input.length() > BUFFERSIZE)
      {
        input = input.substr(0, BUFFERSIZE);
      }

      n = write(sockfd, input.c_str(), input.length());

      if(n < 0)
      {
        cout << "ERROR writing to socket" << endl;
        break;
      }

      bzero(buffer,BUFFERSIZE);
      n = read(sockfd, buffer, BUFFERSIZE-1);

      cout << buffer << endl;

      if(n < 0)
      {
        cout << "ERROR reading from socket" << endl;
        break;
      }
    }

    close(sockfd);
  }

  void TcpSocket::Listen(string ip, int port)
  {
    AddressInfo addressInfo;
    addressInfo.ip = ip;
    addressInfo.port = port;

    Threading::ThreadManager::SpawnThread(this, &TcpSocket::RunListener, addressInfo);
  }

  void TcpSocket::RunListener(AddressInfo addressInfo)
  {
    int sockfd, newsockfd;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    string message;
    LogEventArgs* logEventArgs = new LogEventArgs;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd < 0)
    {
      cout << "ERROR opening socket" << endl;
      return;
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(addressInfo.port);

    if(bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
      logEventArgs->SetMessage("Socket could not bind");
      logEventArgs->SetLevel(Error);
      this->Fire("tcp.log", logEventArgs);

      delete logEventArgs;

      return;
    }

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    this->isListening = true;
    while(this->isListening)
    {
      logEventArgs->SetMessage("Waiting for client");
      logEventArgs->SetLevel(Error);
      this->Fire("tcp.log", logEventArgs);

      newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

      Threading::ThreadManager::SpawnThread(this, &TcpSocket::HandleClient, newsockfd);
    }

    close(sockfd);
  }

  void TcpSocket::HandleClient(int sockfd)
  {
    char buffer[BUFFERSIZE];
    string message;
    int n;
    LogEventArgs* logEventArgs = new LogEventArgs;
    TcpEventArgs* tcpEventArgs = new TcpEventArgs("");

    if(sockfd < 0)
    {
      logEventArgs->SetMessage("Socket not eccepted");
      logEventArgs->SetLevel(Error);
      this->Fire("tcp.log", logEventArgs);

      delete logEventArgs;

      return;
    }

    while(true)
    {
      bzero(buffer, BUFFERSIZE);
      n = read(sockfd, buffer, BUFFERSIZE-1);

      if(n < 0)
      {
        logEventArgs->SetMessage("Could not read from socket");
        logEventArgs->SetLevel(Error);
        this->Fire("tcp.log", logEventArgs);
        break;
      }

      message = string(buffer);

      logEventArgs->SetMessage("Received message :: " + message);
      logEventArgs->SetLevel(Debug);
      this->Fire("tcp.log", logEventArgs);

      tcpEventArgs->SetMessage(message);
      this->Fire("tcp.receive", tcpEventArgs);

      // TODO - Extract this snippit to its own functions
      //        and build an incomming and outgoing message queue
      n = write(sockfd, "I got your message", 18);

      if(n < 0)
      {
        logEventArgs->SetMessage("Could not write to socket");
        logEventArgs->SetLevel(Error);
        this->Fire("tcp.log", logEventArgs);
        break;
      }
    }

    delete logEventArgs;
    delete tcpEventArgs;

    close(sockfd);
  }

  void TcpSocket::Stop()
  {
    this->isListening = false;
    this->connected = false;
  }

  bool TcpSocket::Send(string message)
  {
    this->queue.Push(message);
    return false;
  }

  int TcpSocket::Read(int method)
  {
    return method;
  }

  void TcpSocket::OnReceive(TcpEventArgs* args)
  {
    cout << args->ToString() << endl;
  }
}
