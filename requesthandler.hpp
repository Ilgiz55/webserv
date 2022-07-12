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

	bool static_site;
	bool isfile;

public:
	RequestHandler(ConfigServer conf, Request& req, Response& res);
	~RequestHandler() {}
	void Get(AConfig& config);
	void Post(AConfig& config);
	void Delete();

	void ParseFileType();
	void GetPath();
	AConfig GetConf();
	void GetForFile(std::string path, AConfig conf);
	void GetForDir(std::string path);
	void AutoIndex();

	void Handle();
};

#endif