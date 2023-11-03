#include "Client.h"

int main(int argc, char* argv[]) {
    std::string ip = "127.0.0.1";
    int port = 5555;

    if (argc > 2) {
        ip = argv[1];
        port = std::stoi(argv[2]);
    }

    Client client(ip, port);

    if (!client.initializeWSA()) return 0;

    if (client.createSocket() == INVALID_SOCKET) return 0;

    if (!client.connectToServer()) return 0;

    std::string cmd;
    std::cout << "Enter your command: ";
    std::getline(std::cin, cmd);

    client.sendCommand(cmd);

    return 0;
}

