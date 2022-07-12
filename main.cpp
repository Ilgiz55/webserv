#include "session.hpp"
#include "server.hpp"
#include "./config/ConfigPars.hpp"

// static int port = 8888;

int main(int agrc, char **argv)
{
    // std::vector<std::pair<std::string, int> > lis;
    // lis.push_back(std::pair<std::string, int>("127.0.0.1", 8080));
    // lis.push_back(std::pair<std::string, int>("127.0.0.1", 8008));
    // lis.push_back(std::pair<std::string, int>("127.0.0.1", 8888));

    std::vector<Server*> serv;
    std::string config_file = "config_test.conf";
    ConfigPars *conf = new ConfigPars(config_file);
    EventSelector *selector = new EventSelector;

    // std::vector<std::pair<std::string,int> >::iterator it = lis.begin();
    std::vector<ConfigServer>::iterator it = conf->getConfigs().begin();
    std::vector<ConfigServer>::iterator it_end = conf->getConfigs().end();
    int i = 1;
    for(; it != it_end; ++it ) {
        // std::cout << "Server: " << i++ << std::endl;
        // (*it).printConfigServer();
        serv.push_back(Server::Start(*it, selector, (*it).getListen()));
    }

    // if (!serv)
    //     return 1;
    try
    {
        selector->Run();
    }
    catch(const std::exception& e)
    {
        std::cerr << "WTHF" << std::endl;
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}