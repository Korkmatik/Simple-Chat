#include "SimpleClientMenu.hpp"
#include "ExceptionLogger.hpp"

#include <iostream>
#include <conio.h>
#include <memory>

SimpleClientMenu::SimpleClientMenu()
{}

void SimpleClientMenu::start()
{
	getIpAddressFromUser();
	getPortFromUser();
	getNicknameFromUser();		
	startClient();
}

void SimpleClientMenu::getIpAddressFromUser()
{
	std::cout << " Enter Server Ip-Address(Nothing for localhost): ";
	getline(std::cin, ipAddress);
	if (ipAddress.compare("") == 0)
		ipAddress = "127.0.0.1";

	std::cout << " [*]Server Ip-Address set to: " << ipAddress << std::endl;
}

void SimpleClientMenu::getPortFromUser()
{
	std::cout << " Enter Server port: ";
	std::string portStr;
	getline(std::cin, portStr);
	port = std::stoi(portStr);

	std::cout << " [*]Server port set to: " << port << std::endl;
}

void SimpleClientMenu::getNicknameFromUser()
{
	std::cout << " Enter your desired nickname: ";
	getline(std::cin, nickname);

	std::cout << " [*]Nickname set to: " << nickname << std::endl;
}

void SimpleClientMenu::startClient()
{
	std::cout << " Press a key to connect to the server" << std::endl;
	_getch();
	system("cls");

	std::cout << "Starting Client ..\n";
	client = std::make_unique<SimpleClient>(nickname, ipAddress, port);
	try
	{
		client->initialize();
		client->run();
	}
	catch (const std::exception& e)
	{
		ExceptionLogger::logException(e);
	}
}
