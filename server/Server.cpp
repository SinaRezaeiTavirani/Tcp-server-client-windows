#include "Server.h"
#include "Logger.h"


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
        Logger::get_instance()->log("The Winsock dll not found!");
        return false;
    }
    Logger::get_instance()->log("The Winsock dll found");
    Logger::get_instance()->log(std::string("The status: ") + m_wsa_data.szSystemStatus);
    return true;
}

SOCKET Server::createSocket() {
    m_server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_server_socket == INVALID_SOCKET) {
        Logger::get_instance()->log("ERROR at socket(): " + WSAGetLastError());
    } else {
        Logger::get_instance()->log("socket() is OK!");
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
        Logger::get_instance()->log("bind() failed " + WSAGetLastError());
        return false;
    }
    Logger::get_instance()->log("bind() is OK!");
    return true;
}

bool Server::startListening() {
    if (listen(m_server_socket, 2) == SOCKET_ERROR) {
        Logger::get_instance()->log("listen() ERROR listening on socket: " + WSAGetLastError());
        return false;
    }
    Logger::get_instance()->log("listen() is OK");
    return true;
}

SOCKET Server::acceptConnection() {
    SOCKET accept_socket = INVALID_SOCKET;
    accept_socket = accept(m_server_socket, nullptr, nullptr);
    if (accept_socket == INVALID_SOCKET) {
        Logger::get_instance()->log("accept failed: " + WSAGetLastError());
        return INVALID_SOCKET;    
    }
    Logger::get_instance()->log("accepted connection");
    return accept_socket;
}
