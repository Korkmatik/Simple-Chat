#pragma once
class BaseObject
{
public:
	inline BaseObject() {}

	virtual void run() = 0;
	virtual void initialize() = 0;
};

