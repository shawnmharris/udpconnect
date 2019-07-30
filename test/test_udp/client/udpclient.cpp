
#include <string>
#include "udpconnection.h"
#include "sensorgramtypes.h"
#include <stdio.h>

using namespace sensorconnect;

struct Test
{
	uint8 data[1000];
};

int main()
{
	try
	{
		std::unique_ptr<IMessageConnection> udp(new UDPConnection());

		std::string host;
		host = "127.0.0.1";
		uint16 port = 5000;

		char mesg[141];
		memset(&mesg, 0, sizeof(mesg));
		sprintf_s(mesg, "Request Hello World");

		printf("client message [%s] to %s:%d\n", mesg, host.c_str(), port);

		udp->SendTo(host.c_str(), port, mesg, (uint16)strnlen_s(mesg, sizeof(mesg)));
		
		// get response
		memset(&mesg, 0, sizeof(mesg));
		udp->ReceiveFrom(mesg, sizeof(mesg));

		printf("server response message [%s]\n", mesg);
	}
	catch (std::exception e)
	{
		printf("%s\n", e.what());
	}
}

