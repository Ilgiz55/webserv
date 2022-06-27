#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <fstream>
#include <map>
#include <iostream>
#include <algorithm>
#include "utils2.hpp"
#include "ConfigServer.hpp"

#define MAX_PORT 65535

class Config
{
private:
	std::vector<ConfigServer> _configs;

public:
	Config() {}

	Config(std::string& fname) //: _listen(80,""), _server_name(""), _location("")
	{
		std::ifstream ifs_config(fname);
		if (!ifs_config.is_open())
			exit_error("Error open file", 1);
		std::string	str_stream;
		int i = 0;
		while (std::getline(ifs_config, str_stream))
		{
			std::size_t found = str_stream.find("server");
			if (found != std::string::npos)
			{
				std::getline(ifs_config, str_stream);
				_configs.push_back(ConfigServer());
				pars_line(ifs_config, _configs[i], str_stream);
				i++;
			}
			// std::cout << str_stream <<std::endl;
		}
	}

	~Config(){}

	ConfigServer getConfigServer(int i) {
		return _configs[i];
	}

	std::vector<ConfigServer>& getConfigs() { return _configs; }

private:

	void pars_line(std::ifstream& ifs_config, ConfigServer& config_server, std::string& _line)
	{
		std::size_t found = _line.find("}");
		while (found == std::string::npos)
		{
			try
			{
				if ((found = _line.find("listen")) != std::string::npos)
					pars_listen(config_server, _line.erase(found, found + 6));
				else if ((found = _line.find("root")) != std::string::npos)
					pars_root(config_server, _line.erase(found, found + 4));
				if (!std::getline(ifs_config, _line))
					return ;
				found = _line.find("}");
			}
			catch(const std::exception& e)
			{
				std::cerr << "Configuration file error: ";
				exit_error(e.what(), 1);
			}
		}
	}

	void pars_listen(ConfigServer &config_server, std::string & _line) {
		_line.erase(remove_if(_line.begin(),_line.end(),isspace),_line.end());
		std::string host("");
		int port;
		std::size_t found = _line.find(":");
		if (found != std::string::npos)
		{
			host = _line.substr(0, found);
			_line = _line.substr(found + 1);
		}
		std::string::size_type sz;
		port = std::stoi(_line, &sz);
		if (_line.substr(sz) != ";")
			throw std::runtime_error("syntax error");
		if (port < 1 || port > MAX_PORT)
			throw std::runtime_error("port error");
		if (host == "")
			host = "0.0.0.0";
		config_server.setListen(std::make_pair(host, port));
	}
	
	void pars_root(ConfigServer &config_server, std::string & _line) {
		_line.erase(remove_if(_line.begin(),_line.end(),isspace),_line.end());
		std::string host("");
		std::size_t found = _line.find_last_of(";");
		if (found == std::string::npos)
			throw std::runtime_error("syntax error");
		config_server.setRoot(_line.substr(0, found));
	}
	// void pars_location(ConfigServer &config_server, std::string & _line) {}
	// void pars_server_name(ConfigServer &config_server, std::string & _line) {}

};

#endif