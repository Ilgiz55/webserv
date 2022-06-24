#ifndef SERVER_HPP
#define SERVER_HPP

#include "fdhandler.hpp"
#include "selector.hpp"
#include "session.hpp"

#include <netinet/in.h>
#include <iostream>

#include <list>
#include <algorithm>

class Session;

class Server : public FdHandler {
	private:
		EventSelector *selector;
		std::list<Session*> sessions;

		Server(EventSelector *sel, int fd);
		virtual void Handle(bool r, bool w);

	public:
		~Server();
		static Server *Start(EventSelector *sel, int port);
		void RemoveSession(Session *s);
};

#endif