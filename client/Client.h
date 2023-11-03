#ifndef CLIENT_H
#define CLIENT_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <tchar.h>
#include <string>
#include <iostream>

class Client {
private:
    WSADATA m_wsa_data;
    SOCKET m_client_socket;
    int m_port;
    std::string m_ip;

public:
    Client(const std::string& ip, int port);
    ~Client();

    // Setters

    // Operations
    bool initializeWSA();
    SOCKET createSocket();
    bool connectToServer();
    int sendCommand(const std::string& cmd);
    void closeConnection();

};

#endif // CLIENT_H
