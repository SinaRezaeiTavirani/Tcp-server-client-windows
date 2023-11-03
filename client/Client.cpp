#include "Client.h"
#include "Logger.h"

Client::Client(const std::string& ip, int port) 
    : m_client_socket(INVALID_SOCKET), m_ip(ip), m_port(port) {}

Client::~Client() {
    closesocket(m_client_socket);
    WSACleanup();
}

bool Client::initializeWSA() {
    WORD m_version_requested = MAKEWORD(2, 2);
    if (WSAStartup(m_version_requested, &m_wsa_data) != 0) {
        Logger::get_instance()->log("The Winsock dll not found!");
        return false;
    }
    Logger::get_instance()->log("The Winsock dll found");
    Logger::get_instance()->log(std::string("The status: ") + m_wsa_data.szSystemStatus);
    return true;
}

SOCKET Client::createSocket() {
    m_client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_client_socket == INVALID_SOCKET) {
        Logger::get_instance()->log("ERROR at socket(): " + std::to_string(WSAGetLastError()));
        return INVALID_SOCKET;
    }
    Logger::get_instance()->log("socket() is OK!");
    return m_client_socket;
}

bool Client::connectToServer() {
    sockaddr_in service;
    const char* ip = m_ip.c_str();
    service.sin_family = AF_INET;
    InetPton(AF_INET, _T(ip), &service.sin_addr.s_addr);
    service.sin_port = htons(m_port);

    if (connect(m_client_socket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
        Logger::get_instance()->log("Client: connect() Failed to connect. Error: " + std::to_string(WSAGetLastError()));
        return false;
    }
    Logger::get_instance()->log("Client connected successfully!");
    return true;
}

int Client::sendCommand(const std::string& cmd) {
    int byte_count = send(m_client_socket, cmd.c_str(), cmd.length(), 0);
    if (byte_count == SOCKET_ERROR) {
        std::cout << "Client send error " << WSAGetLastError() << "." << std::endl;
        return -1;
    }
    std::cout << "Client: sent " << byte_count << " bytes" << std::endl;
    return byte_count;
}
