#include "AConfig.hpp"

AConfig::AConfig() : _root(""), _index("index.html"), _autoindex(false), _isGeneral(false) {}

AConfig::AConfig(bool isGeneral) : _root(""), _index("index.html"), _autoindex(false), _isGeneral(isGeneral) {}

AConfig::~AConfig() {} 

void AConfig::setRoot(std::string root) { _root = root; }

void AConfig::setMethods(std::vector<std::string> methods) { _methods = methods; }

void AConfig::setMethods(std::string methods) { 
	std::vector<std::string> mthds = ft_split(methods, " "); //WHITESPACE
	std::vector<std::string> allowed_mthds = ft_split(METHODS, " "); //WHITESPACE
	if (mthds.size() > allowed_mthds.size())
		throw std::runtime_error("syntax error in allowed methods");
	for (size_t i = 0; i < mthds.size(); i++)
	{
		std::vector<std::string>::iterator it = std::find(allowed_mthds.begin(), allowed_mthds.end(), mthds[i]);
		if (it == allowed_mthds.end())
			throw std::runtime_error("syntax error in allowed methods"); 
	}
	_methods = mthds;
}

void AConfig::setRedirect(std::string redirect){
	std::vector<std::string> tmp = ft_split(redirect, " ");
	if (tmp.size() != 2)
		throw std::runtime_error("syntax error in redirect");
	_redirect = std::make_pair(tmp[0], tmp[1]);
	int i = atoi(tmp[0].c_str());
	if (i < 100 || i > 999)
		throw std::runtime_error("syntax error in redirect");
}

void AConfig::setIndex(std::string index) { _index = index; }

void AConfig::setAutoIndex(std::string autoindex) { 
	if (autoindex == "off")
		_autoindex = false;
	else if (autoindex == "on")
		_autoindex = true;
	else
		throw std::runtime_error("syntax error in autoindex");
}

void AConfig::setIsGeneral(bool isGeneral) { _isGeneral = isGeneral; }

void AConfig::setCGIPath(std::string cgi_path) { _cgi_path = cgi_path; }

void AConfig::setClientBodySize(const std::string BodySize) {
		_cgi_path = atoll(BodySize.c_str()); // no checks
}

std::string& AConfig::getRoot() { return _root; }

std::vector<std::string>& AConfig::getMethods() { return _methods; }

std::pair<std::string, std::string>& AConfig::getRedirect() { return _redirect; }

std::string& AConfig::getIndex() { return _index; }

bool AConfig::getAutoIndex() { return _autoindex; }

bool AConfig::getIsGeneral() { return _isGeneral; }

std::string& AConfig::getCGIPath() { return _cgi_path; }