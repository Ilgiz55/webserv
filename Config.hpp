#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <fstream>
#include <map>
#include <iostream>
#include <algorithm>
#include "utils2.hpp"

#define MAX_PORT 65535

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

	Config(std::string &fname) : _listen(80,""), _server_name(""), _location("")
	{
		std::ifstream ifs_config(fname);
		if (!ifs_config.is_open())
			exit_error("Error open file", 1);
		std::string	str_stream;
		while (std::getline(ifs_config, str_stream))
		{
			pars_line(*this, str_stream);
			// std::cout << str_stream <<std::endl;
		}
	}

	~Config(){}

	int getPort() const { return _listen.first; }

private:

	void pars_line(Config &conf, std::string & _line)
	{
		std::size_t found = _line.find("listen");
		if (found != std::string::npos)
		{
			_line.erase(found, found + 6);
			_line.erase(remove_if(_line.begin(),_line.end(),isspace),_line.end());
			found = _line.find(":");
			if (found != std::string::npos)
			{
				conf._listen.second = _line.substr(0, found);
				_line = _line.substr(found + 1);
			}
			try
			{
				std::string::size_type sz;
				conf._listen.first = std::stoi(_line, &sz);
				if (_line.substr(sz) != ";")
					throw std::runtime_error("syntax error");
				if (conf._listen.first < 1 || conf._listen.first > MAX_PORT)
					throw std::runtime_error("port error");
			}
			catch(const std::exception& e)
			{
				std::cerr << "Configuration file error: ";
				exit_error(e.what(), 1);
			}
		}
	}	

};

#endif