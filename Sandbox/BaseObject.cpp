#include "BaseObject.hpp"

#include <iostream>
#include <conio.h>

using namespace std;

BaseObject::BaseObject(u_short port)
	: port(port), isCleanedUp(false), isInitialized(false)
{
	WSAData data;
	WORD version = MAKEWORD(2, 2);
	if (WSAStartup(version, &data) != 0) {
		cerr << "Cannot init winsock" << endl;
		_getch();
	}
}


BaseObject::~BaseObject()
{
	WSACleanup();
}
