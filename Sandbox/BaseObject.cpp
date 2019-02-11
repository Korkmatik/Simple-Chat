#include "BaseObject.hpp"

#include <iostream>
#include <conio.h>
#include <WS2tcpip.h>

using namespace std;

BaseObject::BaseObject(unsigned short port)
	: port(port), isCleanedUp(false), isInitialized(false)
{
	WSAData data;
	WORD version = MAKEWORD(2, 2);
	if (WSAStartup(version, &data) != 0)
		throw WinSockInitError();
}


BaseObject::~BaseObject()
{
	WSACleanup();
}
