#pragma once
class BaseSocket
{
public:
	inline BaseSocket() {}

	virtual void run() = 0;
	virtual void initialize() = 0;
};

