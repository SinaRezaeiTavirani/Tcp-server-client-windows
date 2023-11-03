#ifndef CLIENT_H
#define CLIENT_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <tchar.h>
#include <string>

class Client {
private:
    WSADATA m_wsa_data;
    SOCKET m_client_socket;
    int m_port;
    std::string m_ip;

public:
    Client(const std::string& ip, int port);
    ~Client();

    bool initializeWSA();
    SOCKET createSocket();
    bool connectToServer();
};

#endif // CLIENT_H
