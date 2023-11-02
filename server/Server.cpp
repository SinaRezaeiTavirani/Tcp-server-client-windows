#include "Server.h"

Server::Server() : server_socket(INVALID_SOCKET) {}

Server::~Server() {
    closesocket(server_socket);
    WSACleanup();
}

bool Server::initializeWSA() {
    WORD m_version_requested = MAKEWORD(2, 2);
    if (WSAStartup(m_version_requested, &wsa_data) != 0) {
        std::cout << "The Winsock dll not found!" << std::endl;
        return false;
    }
    std::cout << "The Winsock dll found" << std::endl;
    std::cout << "The status: " << wsa_data.szSystemStatus << std::endl;
    return true;
}

SOCKET Server::createSocket() {
    server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_socket == INVALID_SOCKET) {
        std::cout << "ERROR at socket(): " << WSAGetLastError() << std::endl;
    } else {
        std::cout << "socket() is OK!" << std::endl;
    }
    return server_socket;
}

bool Server::bindSocket() {
    sockaddr_in service;
    service.sin_family = AF_INET;
    InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
    service.sin_port = htons(PORT);
    if (bind(server_socket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
        std::cout << "bind() failed " << WSAGetLastError() << std::endl;
        return false;
    }
    std::cout << "bind() is OK!" << std::endl;
    return true;
}

bool Server::startListening() {
    if (listen(server_socket, 2) == SOCKET_ERROR) {
        std::cout << "listen() ERROR listening on socket: " << WSAGetLastError() << std::endl;
        return false;
    }
    std::cout << "listen() is OK" << std::endl;
    return true;
}

SOCKET Server::acceptConnection() {
    SOCKET accept_socket = INVALID_SOCKET;
    accept_socket = accept(server_socket, nullptr, nullptr);
    if (accept_socket == INVALID_SOCKET) {
        std::cout << "accept failed: " << WSAGetLastError() << std::endl;
        return INVALID_SOCKET;    
    }
    std::cout << "accepted connection" << std::endl;
    return accept_socket;
}
