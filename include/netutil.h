#ifndef __NETUTIL_H__
#define __NETUTIL_H__

#include "osheader.h"

namespace sensorconnect
{
	class NetUtil
	{
	public:
		static bool IsNetworkInit();
		static void Init();
		static int GetLastError();
	};
}; 


#endif 