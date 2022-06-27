#ifndef SESSION_HPP
#define SESSION_HPP

#include "fdhandler.hpp"
#include "selector.hpp"
#include "server.hpp"

#include "utils.hpp"
#include "utils2.hpp"

#include <unistd.h>
#include <string.h>
#include <iostream>
#include "request.hpp"
#include "response.hpp"
#include <vector>

#define BUF_LEN 1024

class Server;

class Session : FdHandler {
	friend class Server;
	char buffer[BUF_LEN];
	std::string req;
	Request request;
	Response response;
	Server *master;

	Session(Server *master, int fd);
	~Session();
	void Send();
	void Receive();
	void Parse();
	void SetResponse();
	virtual void Handle(bool r, bool w);

};

#endif