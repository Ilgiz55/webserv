#include "session.hpp"
#include "server.hpp"

// static int port = 8888;

int main(int argc, char **argv)
{
    std::string config_file = "./default/default.conf";
    if (argc > 2)
    {
        std::cout << "!!input error\nusage: ./webserv [config_file.conf]\n";
        return 0;
    }
    else if (argc == 2)
    {
        config_file = argv[1];
        size_t t;
        if ((t = config_file.find(".conf")) != config_file.length() - 5)
        {
            std::cout << "!input error\nusage : ./webserv [config_file.conf]\n";
            return 0;
        }
    }
    
    std::vector<Server*> serv;
    std::vector<ConfigServer> conf = parser_config(config_file);
    EventSelector *selector = new EventSelector;

    std::vector<ConfigServer>::iterator it = conf.begin();
    std::vector<ConfigServer>::iterator it_end = conf.end();
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