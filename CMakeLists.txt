cmake_minimum_required(VERSION 3.8)

include_directories(include)

add_library(sensorconnect
	src/sensorgramclient.cpp
	src/messageaddress.cpp
	src/netutil.cpp
	src/udpconnection.cpp)
