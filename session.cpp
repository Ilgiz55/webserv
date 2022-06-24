#include "session.hpp"

#include <stdio.h>

Session::Session(Server *a_master, int fd) : FdHandler(fd, true), buf_used(0), master(a_master) {}

Session::~Session() {}

void Session::Send(const char *msg) {
	write(GetFd(), msg, strlen(msg));
}

void Session::Receive() {
	int rc = read(GetFd(), buffer, sizeof(buffer));
	if (rc > 0)
		write(1, buffer, rc);
	if (rc < 1)
		master->RemoveSession(this);
}

void Session::Handle(bool r, bool w) {
	if (!r)
		return;
	char answer[] = "\
	HTTP/1.1 200 OK\r\n\
	Version: HTTP/1.1\r\n\
	Content-Type: text/html; charset=utf-8\r\n\
	Content-Length: 88\r\n\r\n\
	<html>hello from my server\n</html>";

	Receive();
	Send(answer);
	printf("connections fd: %d\n", GetFd());
	// master->RemoveSession(this);

}