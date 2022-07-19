#ifndef REQUESTHANDLER_HPP
#define REQUESTHANDLER_HPP

#include "session.hpp"
#include "utils.hpp"
// #include "./cgi/CGI.hpp"

// class Session;

class RequestHandler {
	// Session *session;
	ConfigServer conf_serv;
	Response& response;
	Request& request;
	Location location;
	std::string path;
	// AConfig conf;
	// std::string file_type;

	// std::string root;
	// std::string root_php;
	// std::string root_image;

	// bool static_site;
	// bool isfile;

	RequestHandler();
public:
	RequestHandler(ConfigServer config, Request& req, Response& res);
	~RequestHandler() {}
	// RequestHandler(RequestHandler const &other) { *this = other; };
	// RequestHandler& operator=(RequestHandler const &other) {
	// 	conf_serv = other.getConfServ();
	// 	response = other.getResponce();
	// 	request = other.getRequest();
	// }
	// ConfigServer const &getConfServ() const { return conf_serv; }
	// Response const &getResponce() const { return response; }
	// Request const & getRequest() const { return request; }
	// Location& getLocation() { return location; }
	// std::string& getPath() { return path; }

	void Get(AConfig& conf);
	void Post(AConfig& conf);
	void Delete(AConfig& conf);

	void ParseFileType();
	void GetPath();
	AConfig GetConf();
	void GetForFile(std::string path, AConfig conf);
	void GetForDir(std::string path);
	void AutoIndex();

	void Handle();
};

#endif