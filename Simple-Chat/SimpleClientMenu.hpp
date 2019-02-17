#pragma once

#include "SimpleClient.hpp"

class SimpleClientMenu
{
public:
	SimpleClientMenu();

	void start();

private:
	std::string ipAddress;
	int port;
	std::string nickname;

	std::unique_ptr<SimpleClient> client;	

	void printMenuTitle();
	void getIpAddressFromUser();
	void getPortFromUser();
	void getNicknameFromUser();
	bool userStartsClient();
	void startClient();
};

