#ifndef __IMESSAGECONNECTION_H__
#define __IMESSAGECONNECTION_H__

#include "osheader.h"

struct sockaddr_in;

namespace sensorconnect
{
	class IMessageConnection
	{
	public:
		virtual sockaddr_in ReceiveFrom(char *mesg, unsigned short mesgLen, int flags = 0) = 0;
		virtual void SendTo(const char *host, unsigned short port, 
			const char *mesg, unsigned short mesgLen, int flags = 0) = 0;
		virtual void SendTo(sockaddr_in &addr, const char *mesg, unsigned short mesgLen, int flags = 0) = 0;
		virtual void Bind(const char *host, unsigned short port) = 0;
		virtual void Close() = 0;
	};
}; 

#endif 
