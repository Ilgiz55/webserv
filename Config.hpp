#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <iostream>
#include <map>

class Config
{
private:
	std::pair<int, std::string>	_listen;
	std::string					_server_name;
	std::string					_location;

public:
	Config() : _listen(8888,""), _server_name(""), _location("") {}
	Config(std::pair<int, std::string> lstn, std::string s_name, std::string loc):
				_listen(lstn), _server_name(s_name), _location(loc) {}
	~Config(){}

	int getPort() const { return _listen.first; }
};

#endif