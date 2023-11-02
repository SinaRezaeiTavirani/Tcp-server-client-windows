#ifndef SERVER_H
#define SERVER_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <tchar.h>
#include <iostream>

class Server {
    static Server* instance;

private:

    Server();
    WSADATA wsa_data;
    SOCKET server_socket;
    int port;

public:
    static Server* get_instance();
    ~Server();

    bool initializeWSA();
    SOCKET createSocket();
    bool bindSocket();
    bool startListening();
    SOCKET acceptConnection();
};

#endif // SERVER_CLASS_H
