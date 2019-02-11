#pragma once

#include "BaseObject.hpp"

#include <WS2tcpip.h>
#include <string>

class Client : public BaseObject
{
public:
	Client(u_short port, std::string ipAdress);
	~Client();

	bool init() override;
	void run() override;
	void cleanUp() override;

protected:

private:
	SOCKET sock;
	std::string ipAddress;

	bool isConnected;

	bool connectToServer();

};

