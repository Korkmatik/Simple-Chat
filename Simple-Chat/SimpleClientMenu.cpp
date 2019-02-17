#include "SimpleClientMenu.hpp"

#include <iostream>
#include <conio.h>

SimpleClientMenu::SimpleClientMenu()
{}


SimpleClientMenu::~SimpleClientMenu()
{
}

void SimpleClientMenu::start()
{
	try
	{
		getIpAddressFromUser();
		getPortFromUser();
		getNicknameFromUser();		
		startClient();
	}
	catch (const std::exception& e)
	{
		SYSTEMTIME time;
		GetLocalTime(&time);

		std::cerr << "An error occured(" << time.wDay << "/" << time.wMonth << "/" << time.wYear << " " 
			<< time.wHour << ":" << time.wMinute << "): " << e.what()<< std::endl;
		_getch();
	}
}

void SimpleClientMenu::getIpAddressFromUser()
{
	std::cout << "Enter Server Ip-Address(Nothing for localhost): ";
	getline(std::cin, ipAddress);
	if (ipAddress.compare("") == 0)
		ipAddress = "127.0.0.1";

	std::cout << "Server Ip-Address set to: " << ipAddress << std::endl;
}

void SimpleClientMenu::getPortFromUser()
{
	std::cout << "Enter Server port";
	std::cin >> port;

	std::cout << "Server port set to: " << port << std::endl;
}

void SimpleClientMenu::getNicknameFromUser()
{
	std::cout << "Enter your desired nickname: ";
	getline(std::cin, nickname);

	std::cout << "Nickname set to: " << nickname << std::endl;
}

void SimpleClientMenu::startClient()
{
	std::cout << "Starting Client ..";
	client = std::make_unique<SimpleClient>(nickname, ipAddress, port);
	try
	{
		client->initialize();
		client->run();
	}
	catch (const std::exception& e)
	{
		throw e;
	}
}
