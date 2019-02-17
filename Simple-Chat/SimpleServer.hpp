#pragma once

#pragma comment(lib, "ws2_32.lib")
#include <WS2tcpip.h>
#include <exception>
#include <string>

class SimpleServer
{
public:
	SimpleServer(unsigned int port = 8080);
	~SimpleServer();

	void initialize();
	void run();

private:
	unsigned int port;
	sockaddr_in hint;
	SOCKET listening;
	SOCKET clientSocket;

	bool isWsaInitialized;
};

class WsaStartupFail : std::exception
{
public:
	const char* what() const override
	{
		return "Can't Initialize winsock!";
	}
};

class SocketCreationFail : std::exception
{
public:
	explicit SocketCreationFail(std::string socketType)
		: socketType(socketType)
	{}

	const char* what() const override
	{
		return std::string("Can't create a " + socketType + " socket!").c_str();
	}

private:
	std::string socketType;
};

class BindFail : std::exception
{
public:
	explicit BindFail(int errorCode) 
		: errorCode(errorCode)
	{}

	const char* what() const override
	{
		return std::string("Binding failed with error #" + errorCode).c_str();
	}

private:
	int errorCode;
};

class ReceiveFail : std::exception
{
public:
	const char* what() const override
	{
		return "Error in recv()";
	}
};