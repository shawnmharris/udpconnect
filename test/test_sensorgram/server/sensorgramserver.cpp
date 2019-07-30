
#include <string>
#include <stdio.h>
#include "udpconnection.h"
#include "sensorgramtypes.h"
#include "sensorgramclient.h"
#include "vhd.h"

using namespace sensorconnect;

int main()
{
	try
	{
		// import your connection info from somewhere ...
		std::string host;
		host = "127.0.0.1";
		uint16 port = 5000;

		// create and fill mesgAddr
		MessageAddress serverAddr(host.c_str(), port);

		// create your Sensorphone in smart ptr, sensorclient stores udpconnection in 
		// member smart ptr and disposes on destruction
		std::unique_ptr<ISensorgramClient> server(new SensorgramClient(new UDPConnection));
		server->Bind(serverAddr);

		while (true)
		{
			Sensorgram sg;
			memset(&sg, 0, sizeof(sg));
			printf("server waiting for sensorgram [%s:%d]\n", host.c_str(), port);

			MessageAddress clientAddr = server->ReceiveFrom(&sg);
			
			// process the request
			if (sg.opCode != SENSOROP_SIMU_VHD_REQUEST)
			{
				throw std::system_error(0, std::system_category(), "unexpected sensorgram request");
			}

			if (sg.sequence != 0x01)
			{
				throw std::system_error(0, std::system_category(), "unexpected sensorgram sequence");
			}

			if (sg.ackSequence != 0x00)
			{
				throw std::system_error(0, std::system_category(), "unexpected sensorgram ackSequence");
			}

			if (sg.dataLen != sizeof(VHDRequest))
			{
				throw std::system_error(0, std::system_category(), "unexpected sensorgram payload");
			}

			uint16 qPort = sg.qPort;
			uint32 lastSent = 0x01;
			uint32 lastRecv = sg.sequence;

			// copy sensorgram payload to response
			VHDRequest vhdRequest;
			memset(&vhdRequest, 0, sizeof(vhdRequest));
			memcpy_s(static_cast<void *>(&vhdRequest), sizeof(vhdRequest),
				static_cast<const void *>(sg.data), sg.dataLen);

			printf("received vhdRequest data:\n");
			printf("=========================================\n");
			printf("initialPosition.x=%2.1lf\n", vhdRequest.initPosition.x);
			printf("initialPosition.y=%2.1lf\n", vhdRequest.initPosition.y);
			printf("initialPosition.z=%2.1lf\n", vhdRequest.initPosition.z);
			printf("zTrackGripRR=%3.5lf\n\n", vhdRequest.zTrackGripRR);

			// copy sensorgram payload to response
			VHDResponse vhdResponse;
			memset(&vhdResponse, 0, sizeof(vhdResponse));

			// compose vhdResponse 
			vhdResponse.position.x = 4.0;
			vhdResponse.position.y = 5.0;
			vhdResponse.position.z = 6.0;
			vhdResponse.nWheelRR = 29.12340;

			printf("sending vhdResponse data:\n");
			printf("=========================================\n");
			printf("position.x=%2.1lf\n", vhdResponse.position.x);
			printf("position.y=%2.1lf\n", vhdResponse.position.y);
			printf("position.z=%2.1lf\n", vhdResponse.position.z);
			printf("nWheelRR=%3.5lf\n\n", vhdResponse.nWheelRR);

			// compose sensorgram response
			memset(&sg, 0, sizeof(sg));
			sg.qPort = qPort;
			sg.sequence = lastSent;
			sg.ackSequence = lastRecv;
			sg.opCode = SENSOROP_SIMU_VHD_RESPONSE;
			sg.dataLen = sizeof(vhdResponse);
			memcpy_s(static_cast<void *>(sg.data), sizeof(sg.data),
				static_cast<const void *>(&vhdResponse), sizeof(vhdResponse));

			// send the response
			server->SendTo(sg, clientAddr);
		}
	}
	catch (std::exception e)
	{
		printf("%s\n", e.what());
	}
}

