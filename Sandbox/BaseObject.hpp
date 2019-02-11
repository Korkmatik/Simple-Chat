#pragma once
#include <WS2tcpip.h>

class BaseObject
{
public:
	explicit BaseObject(u_short port);

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
	u_short port;

private:

};

