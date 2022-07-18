#ifndef WEBSERV_LOCATION_HPP
#define WEBSERV_LOCATION_HPP

#include "AConfig.hpp"

class Location : public AConfig
{
private:
	bool _upload_enable;
	std::string	_upload_path;
public:
	Location() : AConfig() {};
	~Location(){};

	void setUploadEnable(std::string& upld_enbl){
		if (upld_enbl == "off")
			_upload_enable = false;
		else if (upld_enbl == "on")
			_upload_enable = true;
		else
			throw std::runtime_error("syntax error in autoindex");
	}
	void setUploadPath(std::string& upload_path) { _upload_path = upload_path; }

	const bool& getUploadEnable() const { return _upload_enable; }
	const std::string& getUploadPath() const {return _upload_path; }

	// void printLocation()
	// {
	// 	std::cout << "	root " << this->getRoot() << std::endl;
	// 	std::vector<std::string>::iterator it = this->getMethods().begin();
    //     std::vector<std::string>::iterator it_end = this->getMethods().end();
    //     std::cout << "	method:";
    //     while (it != it_end)
    //     {
    //         std::cout << " " << *it ;
    //         it++;
    //     }
	// 	std::cout << std::endl << "	index " << this->getIndex() << std::endl;
	// 	std::cout << "	cgi_path " << this->getCGIPath() << std::endl;
	// }
};

#endif //WEBSERV_LOCATION_HPP