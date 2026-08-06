#ifndef FT_IRC_HPP
#define FT_IRC_HPP

//socket, setsockopt, getsockname, bind, connect, listen,
//accept, send, recv, 
#include <sys/socket.h>

//close, lseek
#include <unistd.h>

//getprotobyname, geyhostbyname, getaddrinfo, freeaddrinfo
#include <netdb.h>

//htons, htonl, ntohs, ntohl, inet_addr, inet_ntoa, inet_ntop
#include <arpa/inet.h>

//signal, sigaction, sigemptyset, sigfillset, sigaddset, 
//sigdelset, sigismember
#include <signal.h>

//fstat
#include <sys/stat.h>

//fcntl
#include <fcntl.h>

//epoll...
#include <poll.h>

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <map>

#endif