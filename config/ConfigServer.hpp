#ifndef CONFIGSERVER_HPP
#define CONFIGSERVER_HPP

#include "Location.hpp"
#include "../webserv.hpp"
#include "AConfig.hpp"

class ConfigServer : public AConfig
{
private:
    std::pair<std::string, int>     _listen;
	std::string					    _server_name;
	std::map<std::string, Location> _location;

public:
    ConfigServer() : AConfig(true), _listen(std::make_pair("0.0.0.0", 8000)), _server_name("") {}
    ~ConfigServer() {}

    void setListen(std::string line) {
        line.erase(remove_if(line.begin(),line.end(),isspace),line.end());
    	std::string host("");
        int port;
        std::size_t found = line.find(":");
        if (found != std::string::npos)
        {
            host = line.substr(0, found);
            line = line.substr(found + 1);
        }
        std::string::size_type sz;
        port = std::stoi(line, &sz);
        if (line.substr(sz) != "")
            throw std::runtime_error("syntax error");
        if (port < 1 || port > MAX_PORT)
            throw std::runtime_error("port error");
        if (host == "")
            host = "0.0.0.0";
        if (host == "location")
            host = "127.0.0.1";
        _listen = std::make_pair(host, port);
    }
    void setServerName(std::string s_name) { _server_name = s_name; }
    void setLocation(std::pair<std::string, Location> lctn) { _location.insert(lctn); }
    std::map<std::string, Location>& getLocation() { return _location; }
    std::pair<std::string, int>& getPort() { return _listen; }

    //check pars
    // void printConfigServer()
    // {
    //     std::cout << "listen " << _listen.first << " " << _listen.second << std::endl;
    //     std::cout << "server_name " << _server_name << std::endl;
    //     std::cout << "root " << this->getRoot() << std::endl;
	// 	std::cout << "index " << this->getIndex() << std::endl;
	// 	std::cout << "cgi_path " << this->getCGIPath() << std::endl;
    //     std::vector<std::string>::iterator it = this->getMethods().begin();
    //     std::vector<std::string>::iterator it_end = this->getMethods().end();
    //     std::cout << "method:";
    //     while (it != it_end)
    //     {
    //         std::cout << " " << *it ;
    //         it++;
    //     }
    //     std::cout << std::endl;
    //     std::map<std::string, Location>::iterator itm = _location.begin();
    //     std::map<std::string, Location>::iterator itm_end = _location.end();
    //     std::cout << "LOCATION: ";
    //     while (itm != itm_end)
    //     {
    //         std::cout <<(*itm).first << std::endl;
    //         (*itm).second.printLocation();
    //         itm++;
    //     }
    // }
};

#endif