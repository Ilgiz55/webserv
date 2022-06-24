#include "server.hpp"

Server::Server(EventSelector *sel, int fd) : FdHandler(fd, true), selector(sel) {
    selector->Add(this);
}

Server::~Server() {}

Server* Server::Start(EventSelector *sel, int port) {
    int ls, opt, res;

    struct sockaddr_in addr;
    ls = socket(AF_INET, SOCK_STREAM, 0);
    if (ls == -1)
        return 0;
    opt = 1;
    setsockopt(ls, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);
    res = bind(ls, (struct sockaddr *) &addr, sizeof(addr));
    if (res == -1)
        return 0;
    res = listen(ls, 15);
    if (res == -1)
        return 0;
    return new Server(sel, ls);
}

void Server::Handle(bool r, bool w) {
    if (!r)
        return;
    int sd;
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    sd = accept(GetFd(), (struct sockaddr*) &addr, &len);
    if (sd == -1)  
        return;
    sessions.push_front(new Session(this, sd));
    selector->Add(sessions.front());
}

void Server::RemoveSession(Session *s) {
    selector->Remove(s);
    auto tomove = std::find(sessions.begin(), sessions.end(), s);
    if (tomove != sessions.end()) {
        sessions.erase(tomove);
        std::cout << "connection closed... fd: " << (*tomove)->GetFd() << std::endl;
        delete *tomove;
    }
}