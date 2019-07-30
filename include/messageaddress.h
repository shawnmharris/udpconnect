#ifndef __MESSAGEADDRESS_H__
#define __MESSAGEADDRESS_H__

#include "osheader.h"


namespace sensorconnect
{
	class MessageAddress
	{
	public:
		MessageAddress(const char *host, unsigned short port);
		MessageAddress(sockaddr_in addr);
		const std::string &GetHost() const;
		const unsigned short GetPort() const;
		sockaddr_in GetNetAddress() const;
	private:
		std::string m_host;
		unsigned short m_port;
		sockaddr_in m_addr;
	};
}; 

#endif 
