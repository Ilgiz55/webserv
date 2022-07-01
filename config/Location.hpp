#ifndef WEBSERV_LOCATION_HPP
#define WEBSERV_LOCATION_HPP

#include "AConfig.hpp"

class Location : public AConfig
{
// private:
public:
	Location() : AConfig() {};
	~Location(){};

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