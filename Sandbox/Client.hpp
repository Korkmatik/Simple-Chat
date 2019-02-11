#pragma once

#include "BaseObject.hpp"

#include <string>

using namespace std;

class Client : public BaseObject
{
public:
	Client(u_short port, string ipAdress);
	~Client();

	bool init() override;
	void run() override;
	void cleanUp() override;

protected:

private:
	SOCKET sock;
	string ipAddress;

	bool isConnected;

	bool connectToServer();

};

