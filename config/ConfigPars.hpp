#ifndef CONFIGPARS_HPP
#define CONFIGPARS_HPP

#include <fstream>
#include <map>
#include <iostream>
#include <algorithm>
#include "../webserv.hpp"
#include "ConfigServer.hpp"
#include "AConfig.hpp"

// #define MAX_PORT 65535

class ConfigPars
{
private:
	std::vector<ConfigServer> _configs;
public:
	ConfigPars() {}

	ConfigPars(std::string& fname);

	~ConfigPars(){}

	ConfigServer getConfigServer(int i);

	std::vector<ConfigServer>& getConfigs();

private:

	void pars_server(std::ifstream& ifs_config, ConfigServer& config_server, std::string& _line);
	std::string pars_line(std::string & _line, std::string str, int flag);
	// std::vector<std::string> pars_line_vector(std::string & _line, std::string str);
	std::pair<std::string, Location>  pars_location(std::ifstream& ifs_config, ConfigServer& config_server, std::string & _line);

};

#endif