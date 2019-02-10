#pragma once

#include "BaseObject.hpp"

class Server : public BaseObject
{
public:
	Server();
	~Server();

	void start() override;
};