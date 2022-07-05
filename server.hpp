#ifndef SERVER_HPP
#define SERVER_HPP

#include "fdhandler.hpp"
#include "selector.hpp"
#include "session.hpp"
#include "./config/ConfigPars.hpp"

#include <netinet/in.h>
 #include <arpa/inet.h>
#include <iostream>

#include <list>
#include <algorithm>

class Session;

class Server : public FdHandler {
	private:
		EventSelector *selector;
		std::list<Session*> sessions;

		Server(ConfigServer conf, EventSelector *sel, int fd);
		virtual void Handle(bool r, bool w);

	public:
		~Server();
		static Server *Start(ConfigServer conf, EventSelector *sel, std::pair<std::string, int>& ip_port);
		void RemoveSession(Session *s);
};

#endif