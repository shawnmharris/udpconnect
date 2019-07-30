#ifndef __SENSORCONNECT_OSHEADER_H__
#define __SENSORCONNECT_OSHEADER_H__

#include <stdio.h>
#include <string>
#include <cstring>
#include <system_error>
#include <memory>

#ifdef _WIN32
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32")
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
typedef __int64_t SOCKET;
#define SOCKET_ERROR -1
#define SOCKADDR sockaddr
#define INVALID_SOCKET  (SOCKET)(~0)
#define closesocket close
#endif

#define SENSORFAIL(hr) (((SENSORERR)(hr)) < 0)

namespace sensorconnect
{
	typedef unsigned int uint32;
	typedef unsigned short uint16;
	typedef unsigned char uint8;
	typedef long SENSORERR;
};

#endif
