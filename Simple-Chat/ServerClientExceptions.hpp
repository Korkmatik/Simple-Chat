#pragma once

#include <exception>
#include <string>

class WsaStartupFail : public std::exception
{
public:
	WsaStartupFail(int errorCode)
		: errorCode(errorCode)
	{}

	const char* what() const override
	{
		static char errorStr[100];
		sprintf_s(errorStr, "Can't Initialize winsock! Error #%d", errorCode);
		return errorStr;
	}

private:
	int errorCode;
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

// Client
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