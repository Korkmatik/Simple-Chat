#pragma once

#include <string>
#include <WS2tcpip.h>

class SimpleClient
{
public:
	SimpleClient(std::string ipAddress = "127.0.0.1", int port = 8080);
	~SimpleClient();

	void initialize();
	void run();

private:
	std::string ipAddress;
	int port;

	SOCKET sock;
	sockaddr_in hint;

	bool isWsaInitialized;
	bool isSocketInitialized;
};

