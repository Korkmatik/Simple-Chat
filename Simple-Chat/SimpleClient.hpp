#pragma once

#include <string>
#include <WS2tcpip.h>
#include <exception>

class SimpleClient
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

class WsaStartupFail : public std::exception
{
public:
	WsaStartupFail(int errorCode)
		: errorCode(errorCode)
	{}

	const char* what() const override
	{
		static char errorStr[100];
		sprintf_s(errorStr, "Can't start Winsock, Err #%d", errorCode);
		return errorStr;
	}

private:
	int errorCode;
};

class InvalidSocketFail : public std::exception
{
public:
	InvalidSocketFail(int errorCode)
		: errorCode(errorCode)
	{}

	const char* what() const override
	{
		static char errorStr[100];
		sprintf_s(errorStr, "Can't create socket, Err #%d", errorCode);
		return errorStr;
	}

private:
	int errorCode;
};

class ConnectionToSeverFailed : public std::exception
{
public:
	ConnectionToSeverFailed(int errorCode)
		: errorCode(errorCode)
	{}

	const char* what() const override
	{
		static char errStr[100];
		sprintf_s(errStr, "Can't connect to server, Err #%d", errorCode);
		return errStr;
	}

private:
	int errorCode;
};