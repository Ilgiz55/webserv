#include "session.hpp"
#include "server.hpp"
#include "Config.hpp"

// static int port = 8888;

int main(int agrc, char **argv)
{
    std::vector<std::pair<std::string, int> > lis;
    lis.push_back(std::pair<std::string, int>("127.0.0.1", 8080));
    lis.push_back(std::pair<std::string, int>("127.0.0.1", 8008));
    lis.push_back(std::pair<std::string, int>("127.0.0.1", 8888));

    std::vector<Server*> serv;
    std::string config_file = "default.conf";
    Config *conf = new Config(config_file);
    EventSelector *selector = new EventSelector;

    std::vector<std::pair<std::string,int> >::iterator it = lis.begin();

    for(; it != lis.end(); ++it ) {
        serv.push_back(Server::Start(selector, *it));
    }

    // if (!serv)
    //     return 1;
    selector->Run();
    return 0;
}