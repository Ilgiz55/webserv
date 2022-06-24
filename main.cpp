#include "session.hpp"
#include "server.hpp"

static int port = 8888;

int main(int agrc, char **argv) {
    EventSelector *selector = new EventSelector;
    Server *serv = Server::Start(selector, port);
    if (!serv)
        return 1;
    selector->Run();
    return 0;
}