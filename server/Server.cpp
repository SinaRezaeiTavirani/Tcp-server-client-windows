#include "Server.h"
#include "Logger.h"
#include <cstdlib>
#include <sstream>

const size_t BUFFER_SIZE = 200;

Server::Server() : m_server_socket(INVALID_SOCKET)
                    , m_port(0)
                    , m_ip("")
                    , m_accept_socket(INVALID_SOCKET) {}
 

Server* Server::get_instance() 
{
    static Server instance;  // This is the "magic" static instance
    return &instance;
}

Server::~Server() {
    closesocket(m_server_socket);
    WSACleanup();
}

bool Server::initializeWSA() 
{
    auto logger = Logger::get_instance();
    
    WORD versionRequested = MAKEWORD(2, 2);
    if (WSAStartup(versionRequested, &m_wsa_data) != 0) 
    {
        int errorCode = WSAGetLastError();
        logger->log("The Winsock dll not found! Error code: " + std::to_string(errorCode));
        return false;
    }
    logger->log("The Winsock dll found");
    logger->log(std::string("The status: ") + m_wsa_data.szSystemStatus);
    return true;
}


SOCKET Server::createSocket() 
{
    auto logger = Logger::get_instance();

    m_server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_server_socket == INVALID_SOCKET)
    {
        logger->log("ERROR at socket(): " + std::to_string(WSAGetLastError()));
    } 
    else 
    {
        logger->log("socket() is OK!");
    }
    return m_server_socket;
}

bool Server::bindSocket() {
    // Zero out the memory for the structure
    sockaddr_in service = {};

    // Acquire the logger instance once
    auto logger = Logger::get_instance();

    service.sin_family = AF_INET;
    InetPton(AF_INET, m_ip.c_str(), &service.sin_addr.s_addr);
    service.sin_port = htons(m_port);
    
    if (bind(m_server_socket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
        logger->log("bind() failed: " + std::to_string(WSAGetLastError()));
        return false;
    }
    logger->log("bind() is OK!");
    return true;
}


bool Server::startListening() {
    // Acquire the logger instance once
    auto logger = Logger::get_instance();

    if (listen(m_server_socket, SOMAXCONN) == SOCKET_ERROR) {
        logger->log("listen() ERROR listening on socket: " + std::to_string(WSAGetLastError()));
        return false;
    }
    logger->log("listen() is OK");
    return true;
}


SOCKET Server::acceptConnection() {
    // Acquire the logger instance once
    auto logger = Logger::get_instance();

    m_accept_socket = INVALID_SOCKET;
    m_accept_socket = accept(m_server_socket, nullptr, nullptr);
    if (m_accept_socket == INVALID_SOCKET) {
        logger->log("accept failed: " + std::to_string(WSAGetLastError()));
        return INVALID_SOCKET;    
    }
    logger->log("accepted connection");
    return m_accept_socket;
}


std::string CommandExecutor::runCommand(const std::string& cmd) {
    // Generate a unique filename for the temporary file
    std::string tmpFileName = "temp_output_" + std::to_string(std::rand()) + ".txt";

    // Execute the command and redirect its output to the temporary file
    if (std::system((cmd + " > " + tmpFileName).c_str()) != 0) {
        // Command failed to execute
        return "Command execution failed!";
    }

    // Read the command output from the temporary file
    std::ifstream file(tmpFileName);
    if (!file.is_open()) {
        // Failed to open the temporary file
        return "Failed to capture command output!";
    }

    std::string output((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    // Delete the temporary file
    std::remove(tmpFileName.c_str());

    return output;
}



bool Server::receiveData() {
    char receiveBuffer[BUFFER_SIZE] = {};
    int byteCount = recv(m_accept_socket, receiveBuffer, sizeof(receiveBuffer) - 1, 0); // -1 ensures null termination

    auto logger = Logger::get_instance();

    if (byteCount == SOCKET_ERROR) {
        logger->log("Error receiving data: " + std::to_string(WSAGetLastError()));
        return false;
    } else if (byteCount == 0) {
        logger->log("Connection closed gracefully by the client.");
        return false;
    } else {
        std::string receivedData(receiveBuffer, byteCount);  // Construct string using byteCount
        logger->log("Received data: " + receivedData);

        // If you want to execute and log the command within this function:
        std::string commandOutput = CommandExecutor::runCommand(receivedData);
        logger->log("Output of command: " + commandOutput);
        logger->log("********************#######********************");
        return true;
    }
}




