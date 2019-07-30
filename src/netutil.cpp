
#include "netutil.h"


namespace sensorconnect
{
	bool NetUtil::IsNetworkInit()
	{
#ifdef _WIN32
		SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (s == INVALID_SOCKET && WSAGetLastError() == WSANOTINITIALISED) {
			return false;
		}

		closesocket(s);
#endif
		return true;
	}

	void NetUtil::Init()
	{
#ifdef _WIN32
		WSADATA wsaData;
		WORD version = MAKEWORD(2, 2);

		if (WSAStartup(version, &wsaData) != 0)
		{
			throw std::system_error(NetUtil::GetLastError(), std::system_category(), "socket open error");
		}
#endif
	}

	int NetUtil::GetLastError()
	{
#ifdef _WIN32
		return WSAGetLastError();
#else
		return errno;
#endif
	}
} 

