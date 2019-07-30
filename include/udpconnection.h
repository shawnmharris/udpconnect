#ifndef __UDPCONNECTION_H__
#define __UDPCONNECTION_H__

#include "osheader.h"
#include "imessageconnection.h"


namespace sensorconnect
{
	class UDPConnection : public IMessageConnection
	{
	public:
		UDPConnection();
		virtual ~UDPConnection();

		virtual sockaddr_in ReceiveFrom(char *mesg, unsigned short mesgSize, int flags = 0);
		virtual void SendTo(const char *host, unsigned short port,
			const char *mesg, unsigned short size, int flags = 0);
		virtual void SendTo(sockaddr_in &addr, const char *mesg, unsigned short mesgLen, int flags = 0);
		virtual void Bind(const char *host, unsigned short port);
		virtual void Close();

	private:
		SOCKET m_socket;
	};
}; 


#endif
