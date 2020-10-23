#include "cli_Sock_ipc.h"

cli_Sock_ipc::cli_Sock_ipc(string host, unsigned int port) {
    connect(host, port);
}

cli_Sock_ipc::cli_Sock_ipc() {
    Isconnected = false;
}

cli_Sock_ipc::cli_Sock_ipc(int socket) {
    sockfd = socket;
    Isconnected = true;
}

cli_Sock_ipc::~cli_Sock_ipc() {
    disconnect();
}

int cli_Sock_ipc::connect(string host, unsigned int port) {
    cli_Sock_ipc::host = host;
    cli_Sock_ipc::port = port;

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    server = gethostbyname(host.data());
    bcopy((char*) server->h_addr, (char*) &servaddr.sin_addr.s_addr, server->h_length);
    servaddr.sin_port = htons(port);

    if(Isconnected)
        disconnect();

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    keep_sockalive(sockfd);

    for(size_t i = 0; i < 3; i++) { //try to connect no of times.... 
        if(::connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0)
            cerr << "Connecting error: " << errno << "  " << strerror(errno) << "\n";
        else {
            Isconnected = true;
            return 0;
        }
    }

    Isconnected = false;
    return 1;
}

bool cli_Sock_ipc::hasAnError() {
    if(sockfd == -1)
        return true;

    int error = 0;
    socklen_t len = sizeof(error);
    int retval = getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len);

    if(retval != 0 || error != 0)
        return true;
    else
        return false;
}

int cli_Sock_ipc::keep_sockalive(int socket) {
    int yes = 1;

    if(setsockopt(socket, SOL_SOCKET, SO_KEEPALIVE, &yes, sizeof(int)) == -1)
        return -1;

    int idle = 1;

    if(setsockopt(socket, IPPROTO_TCP, TCP_KEEPIDLE, &idle, sizeof(int)) == -1)
        return -1;

    int interval = 1;

    if(setsockopt(socket, IPPROTO_TCP, TCP_KEEPINTVL, &interval, sizeof(int)) == -1)
        return -1;

    int maxpkt = 10;

    if(setsockopt(socket, IPPROTO_TCP, TCP_KEEPCNT, &maxpkt, sizeof(int)) == -1)
        return -1;

    return 0;
}

int cli_Sock_ipc::disconnect() {
    if(!Isconnected)
        return -1;

    close(sockfd);
    Isconnected = false;

    return 0;
}

int cli_Sock_ipc::To_write(string data) {
    if(!Isconnected)
        return 1;

    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    fd_set write_data;
    FD_ZERO(&write_data);
    FD_SET(sockfd, &write_data);

    cout << data << "\n"; //--->do test here

    int Byte_data = 0;

    for(size_t i = 0; i < data.length(); i += Byte_data) {
        FD_ZERO(&write_data);
        FD_SET(sockfd, &write_data);
        int read_value = select(sockfd + 1, NULL, &write_data, NULL, &tv);

        if(read_value == -1)
            cerr << errno << "  " << strerror(errno) << "\n";
        else if(read_value == 0)
            Byte_data = 0;
        else if(read_value > 0 && FD_ISSET(sockfd, &write_data)) {
            Byte_data = ::write(sockfd, data.substr(i, data.length() - i).c_str(), data.length() - i);

            if(Byte_data == -1) {
                cerr << "sending Error data: " << errno << "  " << strerror(errno) << "\n";
                return 1;
            }
        }
    }

    return 0;
}

string cli_Sock_ipc::Do_read() {
    if(!Isconnected)
        return "";

    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    fd_set read_data;
    FD_ZERO(&read_data);
    FD_SET(sockfd, &read_data);

    string response = "";
    unsigned int n = 0;


    do {
        FD_ZERO(&read_data);
        FD_SET(sockfd, &read_data);
        int read_value = select(sockfd + 1, &read_data, NULL, NULL, &tv);

        if(read_value <= -1)
            cerr << errno << "  " << strerror(errno) << "\n";
        else if(read_value == 0)
            break;
        else if(read_value > 0 && FD_ISSET(sockfd, &read_data)) {

            int tn = ::read(sockfd, recv, buffer_Size - 1);//signs comparision warning

            if(tn > 0) {
                n = tn;
                recv[n] = '\0';
                string read_Resp(recv, n);
                response += read_Resp;
            }
            else if(tn == -1) {
                if(errno == 11) { // connection to get data when suddenly server closed. very important i will explain tomorrow.
                    string read_Resp(recv);

                    if(read_Resp.find_first_not_of("Nara_Simha_Reddy any response") == std::string::npos)
                        response += read_Resp;
                }
                else
                    cerr << errno << "  " << strerror(errno) << "\n";

                break;
            }
            else
                break;

        }
        else
            cerr << "ERROR:  " << read_value << "\n";

    }
    while(n >= buffer_Size - 1);

    return response;
}

string cli_Sock_ipc::read_exit() {
    string read_all = Do_read();

    while(read_all.find("Completed") == string::npos)
        read_all += Do_read();

    read_all = read_all.substr(0, read_all.find("Completed")); //exit message to server

    return read_all;
}

//*****************Nara_Simha_Reddy_10_23_2020_1:05AM_completed*********************************//