#ifndef ACONFIG_HPP
#define ACONFIG_HPP

#include "../webserv.hpp"

class AConfig // abstruct?
{
private:
	// std::string					_server_name;
	std::string 				_root;
	std::vector<std::string>	_methods;
	std::pair<std::string, std::string>	_redirect;
	std::string 				_index;
	bool 						_autoindex;
	bool 						_isGeneral;
	std::string 				_cgi_path;
	size_t 						_client_body_size;
	
public:
    AConfig();
    AConfig(bool isGeneral);
    virtual ~AConfig();

	void setRoot(std::string root);
	void setMethods(std::vector<std::string> methods);
	virtual void setMethods(std::string methods);
	void setRedirect(std::string redirect);
	void setIndex(std::string index);
	void setAutoIndex(std::string autoindex);
	void setIsGeneral(bool isGeneral);
	void setCGIPath(std::string cgi_path);
	void setClientBodySize(const std::string BodySize);

	std::string& getRoot();
	std::vector<std::string>& getMethods();
	std::pair<std::string, std::string>& getRedirect();
	std::string& getIndex();
	bool getAutoIndex();
	bool getIsGeneral();
	std::string &getCGIPath();
};

#endif