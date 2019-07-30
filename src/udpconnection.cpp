
#include "udpconnection.h"
#include "netutil.h"


namespace sensorconnect
{
	UDPConnection::UDPConnection()
	{
		if (!NetUtil::IsNetworkInit())
		{
			NetUtil::Init();
		}

		m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		
		if (m_socket == INVALID_SOCKET)
		{
			throw std::system_error(NetUtil::GetLastError(), std::system_category(), "socket open error");
		}
	}


	UDPConnection::~UDPConnection()
	{
		// clean up
		closesocket(m_socket);
	}

	sockaddr_in UDPConnection::ReceiveFrom(char *mesg, unsigned short mesgLen, int flags)
	{
		sockaddr_in addr;
		socklen_t addrSize = sizeof(addr);
		int ret = recvfrom(m_socket, mesg, mesgLen, flags, reinterpret_cast<SOCKADDR *>(&addr), &addrSize);
		
		if (ret == SOCKET_ERROR)
		{
			throw std::system_error(NetUtil::GetLastError(), std::system_category(), "recvfrom error");
		}

		return addr;
	}


	void UDPConnection::SendTo(const char *host, unsigned short port, 
		const char *mesg, unsigned short mesgLen, int flags)
	{
		sockaddr_in addr;
		addr.sin_family = AF_INET;
		inet_pton(AF_INET, host, &addr.sin_addr);
		addr.sin_port = htons(port);

		int ret = sendto(m_socket, mesg, mesgLen, flags, reinterpret_cast<SOCKADDR *>(&addr), sizeof(addr));
		if (ret == SOCKET_ERROR)
		{
			throw std::system_error(NetUtil::GetLastError(), std::system_category(), "sendto error");
		}
	}

	void UDPConnection::SendTo(sockaddr_in &addr, const char *mesg, unsigned short mesgLen, int flags)
	{
		int ret = sendto(m_socket, mesg, mesgLen, flags, reinterpret_cast<SOCKADDR *>(&addr), sizeof(addr));

		if (ret == SOCKET_ERROR)
		{
			throw std::system_error(NetUtil::GetLastError(), std::system_category(), "sendto error");
		}
	}

	void UDPConnection::Bind(const char *host, unsigned short port)
	{
		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
		addr.sin_port = htons(port);

		int ret = bind(m_socket, reinterpret_cast<SOCKADDR *>(&addr), sizeof(addr));
		
		if (ret == SOCKET_ERROR)
		{
			throw std::system_error(NetUtil::GetLastError(), std::system_category(), "bind error");
		}
	}

	void UDPConnection::Close()
	{
		closesocket(m_socket);
	}
} 


