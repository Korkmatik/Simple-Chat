#pragma once

#include "BaseObject.hpp"

#include <string>
#include <WS2tcpip.h>
#include <exception>

class SimpleClient : public BaseObject
{
public:
	SimpleClient(std::string& nickname, std::string ipAddress = "127.0.0.1", int port = 54000);
	~SimpleClient();

	void initialize();
	void run();

private:
	std::string ipAddress;
	int port;
	std::string nickname;

	SOCKET sock;
	sockaddr_in hint;

	bool isWsaInitialized;
	bool isSocketInitialized;
};

