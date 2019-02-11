#pragma once
#include <exception>

class BaseObject
{
public:
	explicit BaseObject(unsigned short port);

	BaseObject(BaseObject& other) = delete;
	BaseObject& operator=(BaseObject& other) = delete;
	BaseObject(BaseObject&& other) = delete;
	BaseObject& operator=(BaseObject&& other) = delete;

	virtual ~BaseObject();

	virtual bool init() = 0;
	virtual void run() = 0;
	virtual void cleanUp() = 0;

protected:
	bool isCleanedUp;
	unsigned short port;

	bool isInitialized;

private:

};

class InvalidSocket : public std::exception 
{
public:
	const char* what() const override
	{
		return "Could not create a socket";
	}
};

class WinSockInitError : public std::exception
{
public:
	const char* what() const override
	{
		return "Can't initialize WinSock";
	}

};