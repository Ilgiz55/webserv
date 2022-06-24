#include "session.hpp"
#include "server.hpp"

static int port = 8888;

int main() {
    EventSelector *selector = new EventSelector;
    Server *serv = Server::Start(selector, port);
    if (!serv)
        return 1;
    selector->Run();
    return 0;
}