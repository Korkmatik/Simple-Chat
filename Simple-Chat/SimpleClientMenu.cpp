#include "SimpleClientMenu.hpp"
#include "ExceptionLogger.hpp"

#include <iostream>
#include <conio.h>
#include <memory>

SimpleClientMenu::SimpleClientMenu()
{}

void SimpleClientMenu::start()
{
	printMenuTitle();
	getIpAddressFromUser();
	getPortFromUser();
	getNicknameFromUser();		
	if (userStartsClient())
		startClient();
}

void SimpleClientMenu::printMenuTitle()
{
	system("cls");
	std::cout <<
		"         Client configurations\n"
		"+-----------------------------------------+\n"
		" [i]If a default configuration is given,\n"
		"    just hit enter to choose it\n"
		"+-----------------------------------------+\n";
}

void SimpleClientMenu::getIpAddressFromUser()
{
	std::cout << " [>]Enter Server Ip-Address(Nothing for localhost): ";
	getline(std::cin, ipAddress);
	if (ipAddress.compare("") == 0)
		ipAddress = "127.0.0.1";

	std::cout << " [*]Server Ip-Address set to: " << ipAddress << std::endl;
}

void SimpleClientMenu::getPortFromUser()
{
	bool portIsSet = false;

	while (!portIsSet) {
		std::cout << " [>]Enter Server port(default=54000): ";
		std::string portStr;
		getline(std::cin, portStr);
		if (portStr.compare("") != 0) {
			try
			{
				port = std::stoi(portStr);
			}
			catch (std::invalid_argument&)
			{
				std::cerr << " [-]Sorry, port must be an integer! Try again." << std::endl;
				continue;
			}
		}
		else
			port = 54000;

		portIsSet = true;
	}

	std::cout << " [*]Server port set to: " << port << std::endl;
	
}

void SimpleClientMenu::getNicknameFromUser()
{
	std::cout << " [>]Enter your desired nickname: ";
	getline(std::cin, nickname);

	std::cout << " [*]Nickname set to: " << nickname << std::endl;
}

bool SimpleClientMenu::userStartsClient()
{
	std::cout << "\n [i]You have entered these informations:" <<
		"\n \tServer IP-Address: " << ipAddress <<
		"\n \tServer Port: " << port <<
		"\n \tNickname: " << nickname <<
		"\n [?]Do you want to connect to the server?(y/n) ";

	wint_t userInput = _getwch();
	std::cout << char(userInput) << std::endl;
	
	if (userInput == 'y' || userInput == 'Y')
		return true;
	else {
		std::cout << " [>]Press a key to return to menu" << std::endl;
		_getwch();
		return false;
	}
}

void SimpleClientMenu::startClient()
{
	system("cls");

	std::cout << "[*]Starting Client ...\n";
	
	try
	{
		client = std::make_unique<SimpleClient>(nickname, ipAddress, port);
		client->initialize();
		client->run();
		client.reset();
	}
	catch (const std::exception& e)
	{
		ExceptionLogger::logException(e);
	}

	
}
