#ifndef CONFIGSERVER_HPP
#define CONFIGSERVER_HPP

#include "utils.hpp"
#include "utils2.hpp"

class ConfigServer
{
private:
    std::pair<std::string, int>	_listen;
	std::string					_server_name;
	std::string					_location;
	std::string					_root;
public:
    ConfigServer() {}
    ConfigServer(const ConfigServer& src) : _listen(src._listen), _server_name(src._server_name), _location(src._location), _root(src._root) {}
    ~ConfigServer() {}

    void setListen(std::pair<std::string, int> lstn) { _listen = lstn; }
    void setServerName(std::string s_name) { _server_name = s_name; }
    void setLocation(std::string lctn) { _location = lctn; }
    void setRoot(std::string rt) { _root = rt; }

    std::pair<std::string, int>& getPort() { return _listen; }
    std::string getRoot() { return _root; }
};

#endif