#include "session.hpp"
#include "server.hpp"
#include "Config.hpp"

static int port = 8888;

int main(int agrc, char **argv)
{
    std::string config_file = "default.conf";
    Config *conf = new Config(config_file);
    EventSelector *selector = new EventSelector;
    Server *serv = Server::Start(selector, conf);
    if (!serv)
        return 1;
    selector->Run();
    return 0;
}