#pragma once

#include "BaseObject.hpp"

#include <WS2tcpip.h>
#include <string>

class Server : public BaseObject
{
public:
	explicit Server(u_short port, std::string serverName);
	~Server();

	bool init() override;
	void run() override;
	void cleanUp() override;

private:
	SOCKET listening;
	fd_set master;
	unsigned connectedClients;

	std::string serverName;
};

class ServerNotInitialized : public std::exception
{
public:
	const char* what() const override
	{
		return "Server is not initialized yet";
	}
};