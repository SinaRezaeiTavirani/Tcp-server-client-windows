#include "Server.h"

int main(int argc, char* argv[]) {

    char* ip = argv[1];
    int port = std::stoi(argv[2]);

    Server::get_instance()->set_config(ip, port);

    if (!Server::get_instance()->initializeWSA()) return 0;

    if (Server::get_instance()->createSocket() == INVALID_SOCKET) return 0;

    if (!Server::get_instance()->bindSocket()) return 0;

    if (!Server::get_instance()->startListening()) return 0;

    if (Server::get_instance()->acceptConnection() == INVALID_SOCKET) return -1;

    return 0;
}
