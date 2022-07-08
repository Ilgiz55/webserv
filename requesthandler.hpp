#ifndef REQUESTHANDLER_HPP
#define REQUESTHANDLER_HPP

#include "session.hpp"
#include "utils.hpp"

// class Session;

class RequestHandler {
	// Session *session;
	ConfigServer conf;
	Response& response;
	Request& request;
	std::string path;
	std::string file_type;

	std::string root;
	std::string root_php;
	std::string root_image;

	bool static_site;
	bool isfile;

public:
	RequestHandler(FdHandler *s, Request& req, Response& res);
	~RequestHandler() {}
	void Get();
	void Post();
	void Delete();

	void ParseFileType();
	void GetPath();

	void Handle();
};

#endif