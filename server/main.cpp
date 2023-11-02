#include "Server.h"

int main() {
    Server server;

    if (!server.initializeWSA()) return 0;

    if (server.createSocket() == INVALID_SOCKET) return 0;

    if (!server.bindSocket()) return 0;

    if (!server.startListening()) return 0;

    if (server.acceptConnection() == INVALID_SOCKET) return -1;

    return 0;
}
