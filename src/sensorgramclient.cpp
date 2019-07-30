
#include "sensorgramclient.h"
#include "netutil.h"


namespace sensorconnect
{
	SensorgramClient::SensorgramClient(IMessageConnection *c) : m_connect(c)
	{
		if (!m_connect)
		{
			throw std::system_error(0, std::system_category(), "message connector is null");
		}
	}


	SensorgramClient::~SensorgramClient()
	{
	}
	

	MessageAddress SensorgramClient::ReceiveFrom(Sensorgram *r)
	{
		sockaddr_in addr = m_connect->ReceiveFrom(reinterpret_cast<char *>(r), SENSORGRAM_MAXSIZE);
		return MessageAddress(addr);
	}
	
	
	void SensorgramClient::SendTo(const Sensorgram &r, const MessageAddress &ma) 
	{
		sockaddr_in addr = ma.GetNetAddress();
		m_connect->SendTo(addr, reinterpret_cast<const char *>(&r), sensorgramSize(&r));
	}


	void SensorgramClient::Bind(const MessageAddress &ma)
	{
		m_connect->Bind(ma.GetHost().c_str(), ma.GetPort());
	}

	unsigned short SensorgramClient::sensorgramSize(const Sensorgram *r) 
	{
		return (SENSORGRAM_MAXSIZE - SENSORGRAM_MAXDATA + r->dataLen);
	}
} 


