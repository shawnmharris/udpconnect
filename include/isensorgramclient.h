#ifndef __ISENSORGRAMCLIENT_H__
#define __ISENSORGRAMCLIENT_H__

#include "osheader.h"
#include "sensorgram.h"
#include "messageaddress.h"

namespace sensorconnect
{
	class ISensorgramClient
	{
	public:
		virtual MessageAddress ReceiveFrom(Sensorgram *r) = 0;
		virtual void SendTo(const Sensorgram &r, const MessageAddress &ma) = 0;
		virtual void Bind(const MessageAddress &ma) = 0;
	};
}; 

#endif 

