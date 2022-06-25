#ifndef SESSION_HPP
#define SESSION_HPP

#include "fdhandler.hpp"
#include "selector.hpp"
#include "server.hpp"

#include "utils.hpp"

#include <unistd.h>
#include <string.h>
#include <iostream>
#include "request.hpp"
#include <vector>

#define BUF_LEN 1024

class Server;

class Session : FdHandler {
	friend class Server;
	char buffer[BUF_LEN];
	std::string req;
	Request request;
	Server *master;

	Session(Server *master, int fd);
	~Session();
	void Send(const char *msg);
	void Receive();
	void Parse();
	virtual void Handle(bool r, bool w);

};

#endif