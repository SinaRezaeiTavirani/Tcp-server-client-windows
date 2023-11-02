#include "Server.h"

int main() {

    
    if (!Server::get_instance()->initializeWSA()) return 0;

    if (Server::get_instance()->createSocket() == INVALID_SOCKET) return 0;

    if (!Server::get_instance()->bindSocket()) return 0;

    if (!Server::get_instance()->startListening()) return 0;

    if (Server::get_instance()->acceptConnection() == INVALID_SOCKET) return -1;

    return 0;
}
