#pragma once

#include "BaseObject.hpp"

#include <conio.h>
#include <string>
#include <iostream>

using namespace std;

class Server : public BaseObject
{
public:
	explicit Server(u_short port);
	~Server();

	Server(Server& other) = delete;
	Server& operator=(Server& other) = delete;
	Server(Server&& other) = delete;
	Server& operator=(Server&& other) = delete;


	bool init() override;
	void run() override;
	void cleanUp() override;

private:
	SOCKET listening;
	fd_set master;
};

