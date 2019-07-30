#ifndef __SENSORGRAMCLIENT_H__
#define __SENSORGRAMCLIENT_H__

#include "osheader.h"
#include "sensorgram.h"
#include "isensorgramclient.h"
#include "imessageconnection.h"
#include "messageaddress.h"


namespace sensorconnect
{
	class SensorgramClient : public ISensorgramClient
	{
	public:
		SensorgramClient(IMessageConnection *c);
		virtual ~SensorgramClient();

		virtual MessageAddress ReceiveFrom(Sensorgram *r);
		virtual void SendTo(const Sensorgram &r, const MessageAddress &ma);
		virtual void Bind(const MessageAddress &ma);

	private:
		std::unique_ptr<IMessageConnection> m_connect;
		static unsigned short sensorgramSize(const Sensorgram *r);
	};
}; 

#endif 

