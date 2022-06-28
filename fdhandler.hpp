#ifndef FDHANDLER_HPP
#define FDHANDLER_HPP

#include <unistd.h>
#include "ConfigServer.hpp"

class FdHandler {
    private:
        ConfigServer config;
        int fd;
        bool own_fd;
    public:
        FdHandler(ConfigServer _config, int a_fd, bool own = true) : config(_config), fd(a_fd), own_fd(own) {}
        virtual ~FdHandler() {
            if (own_fd)
                close(fd);
        }
        virtual void Handle(bool r, bool w) = 0;
        int GetFd() const {return fd;}
        ConfigServer GetConfigServer() const {return config;}
        virtual bool WantRead() const {return true;}
        virtual bool WantWrite() const {return false;}
};

#endif