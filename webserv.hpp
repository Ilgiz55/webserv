#ifndef WEBSERV_HPP
#define WEBSERV_HPP

// CPP Includes
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <limits>
#include <cstdio>

// CPP Containers
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <iterator>
#include <list>
#include <utility>


// C Includes
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <limits.h>
#include <errno.h>
#include <dirent.h>

// C System
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/time.h>

// C Network
#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <netinet/in.h>

// Utils
#include "utils.hpp"
#include "utils2.hpp"

// Define two names ntoh functions
// #define ft_htonl ft_ntohl
// #define ft_htons ft_ntohs

// Bytes for endian conversion
// #define BYTE_0 0xff000000
// #define BYTE_1 0x00ff0000
// #define BYTE_2 0x0000ff00
// #define BYTE_3 0x000000ff

// Default
#define RECV_SIZE				65536
#define CGI_BUFSIZE				65536
#define DEFAULT_CONFIG			"./data/www/default.conf"
#define DEFAULT_BUFFER_SIZZE	2142
#define WHITESPACE              " \n\r\t\f\v"
#define MAX_PORT                65535
#define METHODS                 "GET POST DELETE"


# define DEFAULT_CONFIG_PATH        "./default/default.conf"

// Colors
#define RED		"\033[31m"
#define GREEN	"\033[32m"
#define YELLOW	"\033[33m"
#define RESET	"\033[0m"

// Output
// # ifndef OUT
// #  define OUT 1
// # endif
// # ifndef TIME
// #  define TIME 0
// # endif


#endif
