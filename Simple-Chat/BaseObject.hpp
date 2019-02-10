#pragma once
class BaseObject
{
public:
	BaseObject();
	virtual ~BaseObject();

	virtual void start() = 0;
};

