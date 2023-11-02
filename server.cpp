#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <tchar.h>

const int PORT = 5555;

bool initializeWSA(WSADATA& wsa_data) {
    WORD m_version_requested = MAKEWORD(2,2);
    int wsa_err = WSAStartup(m_version_requested, &wsa_data);

    if (wsa_err != 0) {
        std::cout << "The Winsock dll not found!" << std::endl;
        return false;
    }
    
    std::cout << "The Winsock dll found" << std::endl;
    std::cout << "The status: " << wsa_data.szSystemStatus << std::endl;
    return true;
}

SOCKET createSocket() {
    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    if (server_socket == INVALID_SOCKET) {
        std::cout << "ERROR at socket(): " << WSAGetLastError() << std::endl;
        WSACleanup();
    } else {
        std::cout << "socket() is OK!" << std::endl;
    }
    
    return server_socket;
}

bool bindSocket(SOCKET server_socket) {
    sockaddr_in service;
    service.sin_family = AF_INET;
    InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
    service.sin_port = htons(PORT);

    if (bind(server_socket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
        std::cout << "bind() failed " << WSAGetLastError() << std::endl;
        closesocket(server_socket);
        WSACleanup();
        return false;
    }

    std::cout << "bind() is OK!" << std::endl;
    return true;
}

bool startListening(SOCKET server_socket) {
    if (listen(server_socket, 2) == SOCKET_ERROR) {
        std::cout << "listen() ERROR listening on socket: " << WSAGetLastError() << std::endl;
        return false;
    }

    std::cout << "listen() is OK" << std::endl;
    return true;
}

SOCKET acceptConnection(SOCKET server_socket) {
    SOCKET accept_socket = accept(server_socket, nullptr, nullptr);

    if (accept_socket == INVALID_SOCKET) {
        std::cout << "accept failed" << WSAGetLastError() << std::endl;
        return INVALID_SOCKET;
    }

    std::cout << "accepted connection" << std::endl;
    return accept_socket;
}

int main() {
    WSADATA wsa_data;

    if (!initializeWSA(wsa_data)) return 0;

    SOCKET server_socket = createSocket();
    if (server_socket == INVALID_SOCKET) return 0;

    if (!bindSocket(server_socket)) return 0;

    if (!startListening(server_socket)) return 0;

    SOCKET accept_socket = acceptConnection(server_socket);
    if (accept_socket == INVALID_SOCKET) return -1;

    closesocket(server_socket);
    WSACleanup();

    return 0;
}
