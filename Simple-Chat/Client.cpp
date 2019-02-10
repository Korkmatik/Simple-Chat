#include "Client.hpp"

#include <iostream>

Client::Client()
{
}


Client::~Client()
{
}

void Client::start()
{
	std::cout << "Client mode" << std::endl;
	std::cin.get();
}
