
#include <string>
#include "udpconnection.h"
#include "sensorgramtypes.h"

using namespace sensorconnect;

int main()
{
	try
	{
		std::unique_ptr<IMessageConnection> udp(new UDPConnection());

		std::string host;
		host = "127.0.0.1";
		uint16 port = 5000;

		udp->Bind(host.c_str(), port);
		printf("bound server to %s:%d\n", host.c_str(), port);

		char mesg[141];

		while (true)
		{
			memset(&mesg, 0, sizeof(mesg));
			printf("server waiting for message %s:%d\n", host.c_str(), port);

			sockaddr_in clientAddr = udp->ReceiveFrom(mesg, sizeof(mesg));

			printf("server recv new mesg: %s\n", mesg);
			printf("server sending response: [Hello World]\n");

			sprintf_s(mesg, "Hello World");
			udp->SendTo(clientAddr, mesg, (uint16)strnlen_s(mesg, sizeof(mesg)));
		}
	}
	catch (std::exception e)
	{
		printf("%s\n", e.what());
	}
}

