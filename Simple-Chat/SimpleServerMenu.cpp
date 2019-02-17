#include "SimpleServerMenu.hpp"
#include "ExceptionLogger.hpp"

#include <memory>
#include <iostream>

SimpleServerMenu::SimpleServerMenu()
{}

void SimpleServerMenu::start()
{
	printMenuTitle();
	getPortFromUser();
	getNicknameFromUser();
	if(userStartsServer())
		startServer();
}

void SimpleServerMenu::printMenuTitle()
{
	system("cls");
	std::cout <<
		"         Server configurations\n"
		"+-----------------------------------------+\n"
		" If a default configuration is given,\n"
		" just hit enter to choose it\n"
		"+-----------------------------------------+\n";
}

void SimpleServerMenu::getPortFromUser()
{
	bool isPortSet = false;
	
	while (!isPortSet) {
		std::cout << " [>]On which port should the server run?(default=54000): ";
		std::string portStr;
		getline(std::cin, portStr);

		if (portStr.compare("") != 0) {
			try
			{
				port = std::stoi(portStr);
			}
			catch (const std::invalid_argument&)
			{
				std::cerr << " [-]Sorry, port must be an integer! Try again." << std::endl;
				continue;
			}
		}
		else
			port = 54000;

		isPortSet = true;
	}

	std::cout << " [*]Server port set to: " << port << std::endl;
}

void SimpleServerMenu::getNicknameFromUser()
{
	std::cout << " [>]Enter your desired nickname: ";
	getline(std::cin, nickname);
	std::cout << " [*]Nickname set to: " << nickname << std::endl;
}

bool SimpleServerMenu::userStartsServer()
{
	std::cout << "\n [i]You have entered these informations:" <<
		"\n \tServer port: " << port <<
		"\n \tNickname: " << nickname <<
		"\n [?]Do you want to start the server?(y/n) ";
	wint_t userChoice = _getwch();
	std::cout << char(userChoice) << "\n";

	if (userChoice == 'y' || userChoice == 'Y')
		return true;
	else {
		std::cout << " [>]Press any key to return to menu" << std::endl;
		_getwch();
		return false;
	}
	
}

void SimpleServerMenu::startServer()
{	
	system("cls");
	std::cout << "[*]Starting Server ..." << std::endl;

	try
	{
		server = std::make_unique<SimpleServer>(nickname, port);
		server->initialize();
		server->run();
		server.reset();
	}
	catch (const std::exception& e)
	{
		ExceptionLogger::logException(e);
	}
}
