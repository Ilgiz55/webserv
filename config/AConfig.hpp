#ifndef ACONFIG_HPP
#define ACONFIG_HPP

#include "../webserv.hpp"

class AConfig // abstruct?
{
private:
	std::string 				_root;
	std::vector<std::string>	_methods;
	std::string 				_index;
	bool 						_autoindex;
	bool 						_isGeneral;
	std::string 				_cgi_path;
	size_t 						_client_body_size;
	
public:
    AConfig() : _root(""), _index("index.html"), _autoindex(false), _isGeneral(false) {}
    AConfig(bool isGeneral) : _root(""), _index("index.html"), _autoindex(false), _isGeneral(isGeneral) {}
    virtual ~AConfig() {} // virtual?

	void setRoot(std::string root) { _root = root; }
	void setMethods(std::vector<std::string> methods) { _methods = methods; }
	virtual void setMethods(std::string methods) { 
		std::vector<std::string> mthds = ft_split(methods, WHITESPACE);
		std::vector<std::string> allowed_mthds = ft_split(METHODS, WHITESPACE);
		if (mthds.size() > allowed_mthds .size())
			throw std::runtime_error("syntax error in allowed methods");
		for (int i = 0; i < mthds.size(); i++)
		{
			std::vector<std::string>::iterator it = std::find(allowed_mthds.begin(), allowed_mthds.end(), mthds[i]);
			if (it == allowed_mthds.end())
				throw std::runtime_error("syntax error in allowed methods"); 
		}
		_methods = mthds;
	}
	void setIndex(std::string index) { _index = index; }
	void setAutoIndex(std::string autoindex) { 
		if (autoindex == "off")
			_autoindex = false;
		else if (autoindex == "on")
			_autoindex = true;
		else
			throw std::runtime_error("syntax error in autoindex");
	}
	void setIsGeneral(bool isGeneral) { _isGeneral = isGeneral; }
	void setCGIPath(std::string cgi_path) { _cgi_path = cgi_path; }
	void setClientBodySize(const std::string BodySize) {
		 _cgi_path = atoll(BodySize.c_str()); // no checks
	}
	std::string getRoot() { return (_root); }
	std::vector<std::string> getMethods() { return (_methods); }
	std::string getIndex() { return (_index); }
	bool getAutoIndex() { return (_autoindex); }
	bool getIsGeneral() { return (_isGeneral); }
	std::string getCGIPath() { return (_cgi_path); }
};

// void AConfig::setMethods(std::string method) { _methods.push_back(method); }

#endif