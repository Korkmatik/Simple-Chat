#pragma once

#include "BaseObject.hpp"

class Client : public BaseObject
{
public:
	Client();
	~Client();

	void start() override;
};

