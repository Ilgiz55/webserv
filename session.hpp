#ifndef SESSION_HPP
#define SESSION_HPP

#include "fdhandler.hpp"
#include "selector.hpp"
#include "server.hpp"

#include <unistd.h>
#include <string.h>
#include <iostream>

#define BUF_LEN 100

class Server;

class Session : FdHandler {
	friend class Server;
	char buffer[BUF_LEN];
	std::string req;
	int buf_used;
	Server *master;

	Session(Server *master, int fd);
	~Session();
	void Send(const char *msg);
	void Receive();
	void Parse(std::string &str);
	// void ReadAndIgnore();
	// void ReadAndCheck();
	virtual void Handle(bool r, bool w);
};

#endif