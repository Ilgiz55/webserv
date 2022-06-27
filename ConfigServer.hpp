#ifndef CONFIGSERVER_HPP
#define CONFIGSERVER_HPP

#include "utils.hpp"
#include "utils2.hpp"

class ConfigServer
{
private:
    std::vector<std::pair<int, std::string> >	_listen;
	std::string					                _server_name;
	std::string					                _location;
	std::string					                _root;
public:
    ConfigServer() {}
    // ConfigServer() : _server_name(""), _location(""), _root("") { _listen.push_back(std::make_pair(80,"")); }
    ~ConfigServer() {}

    void setListen(std::pair<int, std::string> lstn) { _listen.push_back(lstn); }
    void setServerName(std::string s_name) { _server_name = s_name; }
    void setLocation(std::string lctn) { _location = lctn; }
    void setRoot(std::string rt) { _root = rt; }

    int getPort(int i) { return _listen[i].first; }
};

#endif