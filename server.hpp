#ifndef SERVER_HPP
#define SERVER_HPP

#include "fdhandler.hpp"
#include "selector.hpp"
#include "session.hpp"
#include "Config.hpp"

#include <netinet/in.h>

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
		static Server *Start(EventSelector *sel, Config *conf);
		void RemoveSession(Session *s);
};

#endif