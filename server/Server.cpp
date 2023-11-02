#include "Server.h"


Server::Server() : m_server_socket(INVALID_SOCKET)
                    , m_port(0)
                    , m_ip("") {}
 
Server* Server::instance = nullptr;

Server* Server::get_instance() {
    if (instance == nullptr) {
        instance = new Server();
    }
    return instance;
}

Server::~Server() {
    closesocket(m_server_socket);
    WSACleanup();
}

bool Server::initializeWSA() {
    WORD m_version_requested = MAKEWORD(2, 2);
    if (WSAStartup(m_version_requested, &m_wsa_data) != 0) {
        std::cout << "The Winsock dll not found!" << std::endl;
        return false;
    }
    std::cout << "The Winsock dll found" << std::endl;
    std::cout << "The status: " << m_wsa_data.szSystemStatus << std::endl;
    return true;
}

SOCKET Server::createSocket() {
    m_server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_server_socket == INVALID_SOCKET) {
        std::cout << "ERROR at socket(): " << WSAGetLastError() << std::endl;
    } else {
        std::cout << "socket() is OK!" << std::endl;
    }
    return m_server_socket;
}

bool Server::bindSocket() {
    sockaddr_in service;
    const char* ip = m_ip.c_str();
    service.sin_family = AF_INET;
    InetPton(AF_INET, _T(ip), &service.sin_addr.s_addr);
    service.sin_port = htons(m_port);
    if (bind(m_server_socket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
        std::cout << "bind() failed " << WSAGetLastError() << std::endl;
        return false;
    }
    std::cout << "bind() is OK!" << std::endl;
    return true;
}

bool Server::startListening() {
    if (listen(m_server_socket, 2) == SOCKET_ERROR) {
        std::cout << "listen() ERROR listening on socket: " << WSAGetLastError() << std::endl;
        return false;
    }
    std::cout << "listen() is OK" << std::endl;
    return true;
}

SOCKET Server::acceptConnection() {
    SOCKET accept_socket = INVALID_SOCKET;
    accept_socket = accept(m_server_socket, nullptr, nullptr);
    if (accept_socket == INVALID_SOCKET) {
        std::cout << "accept failed: " << WSAGetLastError() << std::endl;
        return INVALID_SOCKET;    
    }
    std::cout << "accepted connection" << std::endl;
    return accept_socket;
}
