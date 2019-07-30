
#include "messageaddress.h"


namespace sensorconnect
{
	MessageAddress::MessageAddress(const char *host, unsigned short port) 
		: m_host(host), m_port(port)
	{
		int addrLen = sizeof(m_addr);
		memset(&m_addr, 0, addrLen);
		m_addr.sin_family = AF_INET;
		m_addr.sin_port = htons(m_port);
		inet_pton(AF_INET, m_host.c_str(), &m_addr.sin_addr);
	}

	MessageAddress::MessageAddress(sockaddr_in addr) : m_addr(addr)
	{
		char ip[256];
		memset(ip, 0, 256);
		inet_ntop(AF_INET, &m_addr.sin_addr, ip, 256);
		m_port = ntohs(m_addr.sin_port);
		m_host = ip;

	}

	const std::string &MessageAddress::GetHost() const
	{
		return m_host;
	}

	const unsigned short MessageAddress::GetPort() const
	{
		return m_port;
	}

	sockaddr_in MessageAddress::GetNetAddress() const
	{
		return m_addr;
	}

}

