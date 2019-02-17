#pragma once

#include "BaseObject.hpp"
#include "ServerClientExceptions.hpp"

#include <WS2tcpip.h>
#include <exception>
#include <string>

class SimpleServer : public BaseObject
{
public:
	SimpleServer(unsigned int port = 8080);
	~SimpleServer();

	void initialize();
	void run();

private:
	unsigned int port;
	std::string nickname;

	sockaddr_in hint;
	SOCKET listening;
	SOCKET clientSocket;

	bool isWsaInitialized;
};

