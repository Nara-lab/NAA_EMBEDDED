//*****************Nara_Simha_Reddy_10_22_2020_7:20AM_Started*********************************//



#ifndef CLI_SOCK_IPC_H
#define CLI_SOCK_IPC_H

#pragma Pack(1)

#include <iostream>
#include <future>
#include <functional>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/signal.h>


using namespace std;

class cli_Sock_ipc {
  public:
    cli_Sock_ipc(string host, unsigned int port);
    cli_Sock_ipc();
    cli_Sock_ipc(int socket);
   virtual ~cli_Sock_ipc();
    bool hasAnError();
    int connect(string host, unsigned int port);
    int disconnect();

    int To_write(string data);
    string Do_read();
    string read_exit();

	bool Isconnected;
    unsigned int port;
	string host;

  protected:

  private:
    int keep_sockalive(int socket);
    static const unsigned int buffer_Size = 1010;
    int sockfd;
    struct sockaddr_in servaddr;
    char recv[buffer_Size];
    struct hostent* server;
};

#endif // CLI_SOCK_IPC_H