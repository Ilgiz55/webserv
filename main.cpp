#include "session.hpp"
#include "server.hpp"
#include "Config.hpp"

static int port = 8888;

int main(int agrc, char **argv) {
    EventSelector *selector = new EventSelector;
    Config  conf;// = new Config;
    Server *serv = Server::Start(selector, conf);
    if (!serv)
        return 1;
    selector->Run();
    return 0;
}