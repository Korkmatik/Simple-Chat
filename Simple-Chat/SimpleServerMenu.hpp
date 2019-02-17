#pragma once

#include "SimpleServer.hpp"

#include <string>

class SimpleServerMenu
{
public:
	SimpleServerMenu();

	void start();

private:
	std::unique_ptr<SimpleServer> server;

	unsigned int port;
	std::string nickname;

	void getPortFromUser();
	void getNicknameFromUser();
	bool userStartsServer();
	void startServer();
};

