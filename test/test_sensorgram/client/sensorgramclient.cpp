
#include <string>
#include <stdio.h>
#include "udpconnection.h"
#include "sensorgramtypes.h"
#include "sensorgramclient.h"
#include "vhd.h"

using namespace sensorconnect;

struct Test
{
	uint8 data[1000];
};

int main()
{
	// create your Sensorphone in smart ptr, sensorclient stores udpconnection in 
	// member smart ptr and disposes on destruction
	std::unique_ptr<ISensorgramClient> client(new SensorgramClient(new UDPConnection));

	try
	{
		VHDRequest vhdRequest;
		memset(&vhdRequest, 0, sizeof(vhdRequest));

		vhdRequest.initPosition.x = 1.0;
		vhdRequest.initPosition.y = 2.0;
		vhdRequest.initPosition.z = 3.0;
		vhdRequest.zTrackGripRR = 99.96001;

		// import your connection info from somewhere ...
		std::string host;
		host = "127.0.0.1";
		uint16 port = 5000;

		// create and fill mesgAddr
		MessageAddress mesgAddr(host.c_str(), port);

		// create a sensorgram and copy payload (VHDRequest) into it
		Sensorgram sgRequest;
		memset(&sgRequest, 0, sizeof(sgRequest));
		uint16 qPort = rand() % 32767 + 1;
		sgRequest.qPort = qPort;

		uint32 lastSent = 0x01;
		uint32 lastRecv = 0x00;
		sgRequest.sequence = lastSent;
		sgRequest.ackSequence = lastRecv;

		sgRequest.opCode = SENSOROP_SIMU_VHD_REQUEST;
		sgRequest.dataLen = sizeof(vhdRequest);
		memcpy_s(static_cast<void *>(sgRequest.data), sizeof(sgRequest.data),
			static_cast<const void *>(&vhdRequest), sizeof(vhdRequest));

		printf("sending vhdRequest data to [%s:%d]:\n", host.c_str(), port);
		printf("=========================================\n");
		printf("initialPosition.x=%2.1lf\n", vhdRequest.initPosition.x);
		printf("initialPosition.y=%2.1lf\n", vhdRequest.initPosition.y);
		printf("initialPosition.z=%2.1lf\n", vhdRequest.initPosition.z);
		printf("zTrackGripRR=%3.5lf\n\n",    vhdRequest.zTrackGripRR);

		// send your sensorgram
		client->SendTo(sgRequest, mesgAddr);
		
		Sensorgram sgResponse;
		memset(&sgResponse, 0, sizeof(sgResponse));

		// wait for response (this is a blocking call)
		client->ReceiveFrom(&sgResponse);

		// process your reponse
		if (sgResponse.opCode != SENSOROP_SIMU_VHD_RESPONSE)
		{
			throw std::system_error(0, std::system_category(), "unexpected sensorgram response");
		}

		if (sgResponse.sequence != 0x01)
		{
			throw std::system_error(0, std::system_category(), "unexpected sensorgram sequence");
		}

		if (sgResponse.ackSequence != lastSent)
		{
			throw std::system_error(0, std::system_category(), "unexpected sensorgram ackSequence");
		}

		if (sgResponse.qPort != qPort)
		{
			throw std::system_error(0, std::system_category(), "unexpected sensorgram qPort");
		}

		// copy sensorgram payload to response
		VHDResponse vhdResponse;
		memset(&vhdResponse, 0, sizeof(vhdResponse));
		memcpy_s(static_cast<void *>(&vhdResponse), sizeof(vhdResponse),
			static_cast<const void *>(sgResponse.data), sgResponse.dataLen);

		// process your vhdResponse here ...
		printf("received vhdResponse data from [%s:%d]:\n", host.c_str(), port);
		printf("=========================================\n");
		printf("position.x=%2.1lf\n", vhdResponse.position.x);
		printf("position.y=%2.1lf\n", vhdResponse.position.y);
		printf("position.z=%2.1lf\n", vhdResponse.position.z);
		printf("nWheelRR=%3.5lf\n\n", vhdResponse.nWheelRR);

	}
	catch (std::system_error e)
	{
		printf("%s\n", e.what());
	}
}

