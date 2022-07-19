#include "server.hpp"

Server::Server(ConfigServer conf, EventSelector *sel, int fd) : FdHandler(conf, fd, true), selector(sel) {
    selector->Add(this);
}

Server::~Server() {}

Server* Server::Start(ConfigServer conf, EventSelector *sel, std::pair<std::string, int>& ip_port) {
    int ls, opt, res;

    struct sockaddr_in addr;
    
    ls = socket(AF_INET, SOCK_STREAM, 0);
    if (ls == -1)
        return 0;
    opt = 1;
    setsockopt(ls, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    addr.sin_family = AF_INET;
    res = inet_aton(ip_port.first.c_str(), &addr.sin_addr);
    if (res == 0)
        return 0;
    addr.sin_port = htons(ip_port.second);
    res = bind(ls, (struct sockaddr *) &addr, sizeof(addr));
    if (res == -1) {
        return 0;
    }
    res = listen(ls, 15);
    if (res == -1)
        return 0;
	fcntl(ls, F_SETFL, O_NONBLOCK);
    return new Server(conf, sel, ls);
}

void Server::Handle(bool r, bool w) {
    (void)w;
    if (!r)
        return;
    int sd;
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    sd = accept(GetFd(), (struct sockaddr*) &addr, &len);
    if (sd == -1)  
        return;
    fcntl(sd, F_SETFL, O_NONBLOCK);
    sessions.push_front(new Session(this->GetConfigServer(), this, sd));
    selector->Add(sessions.front());
}

void Server::RemoveSession(Session *s) {
    selector->Remove(s);
    std::list<Session*>::iterator tomove = std::find(sessions.begin(), sessions.end(), s);
    if (tomove != sessions.end()) {
        sessions.erase(tomove);
        delete *tomove;
    }
}