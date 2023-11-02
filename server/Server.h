#ifndef SERVER_H
#define SERVER_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <tchar.h>
#include <iostream>
#include <string>

class Server {
    static Server* instance;

private:

    Server();
    WSADATA m_wsa_data;
    SOCKET m_server_socket;
    int m_port;
    std::string m_ip;

public:
    inline void set_config(std::string ip, int port) {
        this->m_ip = ip;    
        this->m_port = port;
    }
    static Server* get_instance();
    ~Server();

    bool initializeWSA();
    SOCKET createSocket();
    bool bindSocket();
    bool startListening();
    SOCKET acceptConnection();
};

#endif // SERVER_CLASS_H
