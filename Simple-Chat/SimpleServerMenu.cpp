#include "SimpleServerMenu.hpp"

#include <memory>
#include <iostream>

SimpleServerMenu::SimpleServerMenu()
{
}


SimpleServerMenu::~SimpleServerMenu()
{
}

void SimpleServerMenu::start()
{
	getPortFromUser();
}

void SimpleServerMenu::getPortFromUser()
{
	std::cout << "\n On which port should the server run?: ";
	std::string portStr;
	getline(std::cin, portStr);
	port = std::stoi(portStr);

	std::cout << " [*]Server port set to: " << port << std::endl;
}

void SimpleServerMenu::startServer()
{
	try
	{
		server = std::make_unique<SimpleServer>(port);
		server->initialize();
		server->run();
	}
	catch (const std::exception& e)
	{
		
	}
}
