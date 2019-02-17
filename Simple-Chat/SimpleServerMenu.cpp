#include "SimpleServerMenu.hpp"
#include "ExceptionLogger.hpp"

#include <memory>
#include <iostream>

SimpleServerMenu::SimpleServerMenu()
{}

void SimpleServerMenu::start()
{
	getPortFromUser();
	getNicknameFromUser();
	if(userStartsServer())
		startServer();
}

void SimpleServerMenu::getPortFromUser()
{
	std::cout << "\n On which port should the server run?: ";
	std::string portStr;
	getline(std::cin, portStr);
	port = std::stoi(portStr);

	std::cout << " [*]Server port set to: " << port << std::endl;
}

void SimpleServerMenu::getNicknameFromUser()
{
	std::cout << " Enter your desired nickname: ";
	getline(std::cin, nickname);
	std::cout << " [*]Nickname set to: " << nickname << std::endl;
}

bool SimpleServerMenu::userStartsServer()
{
	std::cout << "\n You have entered these informations:" <<
		"\n \tServer port: " << port <<
		"\n \tNickname: " << nickname <<
		"\n Do you want to start the server?(y/n) ";
	char userChoice = _getch();
	std::cout << userChoice << "\n";

	if (userChoice == 'y') {
		std::cout << "Press any key to start server" << std::endl;
		_getch();
		return true;
	}
	else {
		std::cout << "Press any key to return to menu" << std::endl;
		_getch();
		return false;
	}
	
}

void SimpleServerMenu::startServer()
{	
	system("cls");
	std::cout << "Starting Server .." << std::endl;

	try
	{
		server = std::make_unique<SimpleServer>(port);
		server->initialize();
		server->run();
	}
	catch (const std::exception& e)
	{
		ExceptionLogger::logException(e);
	}
}
