#ifndef REQUESTHANDLER_HPP
#define REQUESTHANDLER_HPP

#include "session.hpp"
#include "utils.hpp"

class RequestHandler {

	ConfigServer conf_serv;
	Response& response;
	Request& request;
	Location location;
	std::string path;

	RequestHandler();
public:
	RequestHandler(ConfigServer config, Request& req, Response& res);
	~RequestHandler() {}
	void Get(AConfig& conf);
	void Post(AConfig& conf);
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