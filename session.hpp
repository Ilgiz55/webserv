#ifndef SESSION_HPP
#define SESSION_HPP

#include "fdhandler.hpp"
#include "selector.hpp"
#include "server.hpp"

#include <unistd.h>
#include <string.h>

#define BUF_LEN 1024

class Server;

class Session : FdHandler {
	friend class Server;
	char buffer[BUF_LEN];
	int buf_used;
	Server *master;

	Session(Server *master, int fd);
	~Session();
	void Send(const char *msg);
	void Receive();
	virtual void Handle(bool r, bool w);
};

#endif