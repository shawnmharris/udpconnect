#ifndef __SENSORGRAM_H__
#define __SENSORGRAM_H__

#include "osheader.h"

#pragma pack(push, 1)


namespace sensorconnect
{
	// max allowed datagram size is 1412 bytes
	// this allows for some saftey margin of 
	// the standard MTU 1500 minus up to 60 
	// bytes IP header and 8 bytes for udp header
	// 
#define SENSORGRAM_MAXDATA 1400
#define SENSORGRAM_MAXSIZE 1414

	struct Sensorgram
	{
		uint32 sequence;                // optional
		uint32 ackSequence;             // optional
		uint16 qPort;                   // command
		uint16 opCode;                  // command
		uint16 dataLen;                 // payload size
		uint8 data[SENSORGRAM_MAXDATA]; // payload
	};

	/***********************************************
	  Example Packet 1:
	|---------------------------------------------|
	| op | p1 | p2 | len |         data           |
	|---------------------------------------------|
	 op=0x16 (Simulated Camera Video, 
	          Resolution Implied by OpCode)
	 param1 = 0 (not used)
	 param2 = 0 (not used)
	 len=1400
	 data=videoSegment (packed RGB values)
	 
	 struct Pixel
	 { 
		uint8 r; 
		uint8 g;
		uint8 b;
	 }

	 struct VideoSegment
	 {
		int32 offset;
		int32 frame;
		Pixel pixels[464];
	 }

	***********************************************/
}


#pragma pack(pop)


#endif
