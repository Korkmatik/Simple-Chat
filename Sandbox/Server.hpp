#pragma once
#include <WS2tcpip.h>
#include <conio.h>
#include <string>
#include <iostream>

using namespace std;

class Server
{
public:
	Server(u_short port);
	~Server();

	Server(Server& other) = delete;
	Server& operator=(Server& other) = delete;
	Server(Server&& other) = delete;
	Server& operator=(Server&& other) = delete;


	bool init();
	void run();

private:
	SOCKET listening;
	u_short port;
	fd_set master;
};

