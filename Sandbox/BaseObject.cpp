#include "BaseObject.hpp"



BaseObject::BaseObject(u_short port)
	: port(port)
{
	isCleanedUp = false;
}


BaseObject::~BaseObject()
{
	WSACleanup();
}
