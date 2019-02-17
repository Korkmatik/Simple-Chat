#pragma once

#include "BaseObject.hpp"

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

class WsaStartupFail : public std::exception
{
public:
	const char* what() const override
	{
		return "Can't Initialize winsock!";
	}
};

class SocketCreationFail : public std::exception
{
public:
	explicit SocketCreationFail(std::string socketType)
		: socketType(socketType)
	{}

	const char* what() const override
	{
		static char errorStr[100];
		sprintf_s(errorStr, "Can't create a %s socket!", socketType.c_str());
		return errorStr;
	}

private:
	std::string socketType;
};

class BindFail : public std::exception
{
public:
	explicit BindFail(int errorCode) 
		: errorCode(errorCode)
	{}

	const char* what() const override
	{
		static char errorStr[100];
		sprintf_s(errorStr, "Binding failed with error #%d", errorCode);
		return errorStr;
	}

private:
	int errorCode;
};

class ReceiveFail : public std::exception
{
public:
	const char* what() const override
	{
		return "Error in recv()";
	}
};