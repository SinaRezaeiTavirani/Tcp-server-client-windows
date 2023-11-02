#ifndef SERVER_H
#define SERVER_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <tchar.h>
#include <iostream>

class Server {
private:
    WSADATA wsa_data;
    SOCKET server_socket;
    const int PORT = 5555;

public:
    Server();
    ~Server();

    bool initializeWSA();
    SOCKET createSocket();
    bool bindSocket();
    bool startListening();
    SOCKET acceptConnection();
};

#endif // SERVER_CLASS_H
