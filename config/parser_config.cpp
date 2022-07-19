#include "../webserv.hpp"
#include "ConfigServer.hpp"

std::pair<std::string, Location> pars_location(std::ifstream& ifs_config, ConfigServer& config_server, std::string & _line);
std::string pars_line(std::string & _line, std::string str, int flag);
void pars_server(std::ifstream& ifs_config, ConfigServer& config_server, std::string& _line);

std::vector<ConfigServer> parser_config(std::string& fname) //: _listen(80,""), _server_name(""), _location("")
{
	std::ifstream ifs_config(fname);
	if (!ifs_config.is_open())
		exit_error("Error open file", 1);
	std::vector<ConfigServer> _configs;
	try
	{
		std::string	str_stream;
		int i = 0;
		while (std::getline(ifs_config, str_stream))
		{
			str_stream.erase(remove_if(str_stream.begin(),str_stream.end(),isspace),str_stream.end());
			std::size_t found = str_stream.find("server{");
			if (found != std::string::npos)
			{
				std::getline(ifs_config, str_stream);
				_configs.push_back(ConfigServer());
				pars_server(ifs_config, _configs[i], str_stream);
				i++;
			}
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << "Configuration file error: ***";
		exit_error(e.what(), 1);
	}
	return _configs;
}

void pars_server(std::ifstream& ifs_config, ConfigServer& config_server, std::string& _line)
{
	std::size_t found;
	int flag = 0;
	while (_line.find("}") == std::string::npos)
	{
		_line = ft_ltrim(_line);
		if (_line[0] == '#' || _line == "")
			;	
		else if ((found = _line.find("server_name")) != std::string::npos)
			config_server.setServerName(pars_line(_line, "server_name", flag));
		else if ((found = _line.find("root")) != std::string::npos)
			config_server.setRoot(pars_line(_line, "root", flag));
		else if ((found = _line.find("listen")) != std::string::npos)
			config_server.setListen(pars_line(_line, "listen", flag));
		else if ((found = _line.find("allowed_method")) != std::string::npos)
			config_server.setMethods(pars_line(_line, "allowed_method", flag));
		else if ((found = _line.find("autoindex")) != std::string::npos)
			config_server.setAutoIndex(pars_line(_line, "autoindex", flag));
		else if ((found = _line.find("index")) != std::string::npos)
			config_server.setIndex(pars_line(_line, "index", flag));
		else if ((found = _line.find("cgi_path")) != std::string::npos)
			config_server.setCGIPath(pars_line(_line, "cgi_path", flag));
		else if ((found = _line.find("client_body_size")) != std::string::npos)
			config_server.setClientBodySize(pars_line(_line, "client_body_size", flag));
		else if ((found = _line.find("error_page")) != std::string::npos)
			config_server.setErrorPage(pars_line(_line, "error_page", flag));
		else if ((found = _line.find("return")) != std::string::npos)
			config_server.setRedirect(pars_line(_line, "return", flag));
		else if ((found = _line.find("location")) != std::string::npos)
		{
			flag = 1;
			config_server.setLocation(pars_location(ifs_config, config_server, _line));
		}
		else
			throw std::runtime_error("syntax error !");
		if (!std::getline(ifs_config, _line))
			throw std::runtime_error("missing }");
	}
}

std::string pars_line(std::string & _line, std::string str, int flag)
{
	if (flag)
		throw std::runtime_error("location must be determined last");
	_line = ft_ltrim(_line);
	std::size_t found = _line.find(str);
	if (found != 0)
		throw std::runtime_error("syntax error " + str);
	std::string ret = _line.substr(str.length());
	return ft_trim(ret);
}

std::pair<std::string, Location> pars_location(std::ifstream& ifs_config, ConfigServer& config_server, std::string & _line) 
{
	Location loc;
	std::string str = pars_line(_line, "location", 0);
	std::size_t found = str.find_last_of('{');
	if (found == std::string::npos)
		throw std::runtime_error("warning");
	str = ft_trim(str.substr(0,found));
	if (!std::getline(ifs_config, _line))
		throw std::runtime_error("warning");
	while (_line.find("}") == std::string::npos)
	{
		_line = ft_ltrim(_line);
		if (_line[0] == '#' || _line == "")
			;
		else if ((found = _line.find("root")) != std::string::npos)
			loc.setRoot(pars_line(_line, "root", 0));
		else if ((found = _line.find("upload_path")) != std::string::npos)
			loc.setRoot(pars_line(_line, "upload_path", 0));
		else if ((found = _line.find("return")) != std::string::npos)
			config_server.setRedirect(pars_line(_line, "return", 0));
		else if ((found = _line.find("allowed_method")) != std::string::npos)
			loc.setMethods(pars_line(_line, "allowed_method", 0));
		else if ((found = _line.find("autoindex")) != std::string::npos)
			loc.setAutoIndex(pars_line(_line, "autoindex", 0));
		else if ((found = _line.find("upload_enable")) != std::string::npos)
			loc.setAutoIndex(pars_line(_line, "upload_enable", 0));
		else if ((found = _line.find("index")) != std::string::npos)
			loc.setIndex(pars_line(_line, "index", 0));
		else if ((found = _line.find("cgi_path")) != std::string::npos)
			loc.setCGIPath(pars_line(_line, "cgi_path", 0));
		else if ((found = _line.find("client_body_size")) != std::string::npos)
			loc.setClientBodySize(pars_line(_line, "client_body_size", 0));
		if (!std::getline(ifs_config, _line))
			throw std::runtime_error("missing }");
	}
	if (loc.getRoot().empty())
		loc.setRoot(config_server.getRoot());
	if (loc.getMethods().size() == 0)
		loc.setMethods(config_server.getMethods());
	return std::make_pair(str, loc);
}