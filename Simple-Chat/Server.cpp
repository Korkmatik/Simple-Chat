#include "Server.hpp"

#include <iostream>

Server::Server()
{
}


Server::~Server()
{
}

void Server::start()
{
	std::cout << "Server mode" << std::endl;
	std::cin.get();
}
