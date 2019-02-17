#include "Client.hpp"

#include <iostream>
#include <conio.h>

Client::Client(u_short port, std::string ipAddress)
	: BaseObject(port), ipAddress(ipAddress), isConnected(false)
{
	std::cout << "Client created" << std::endl;
}


Client::~Client()
{
	if (!isCleanedUp)
		cleanUp();
}

bool Client::init()
{
	std::cout << "Initalializing client .." << std::endl;

	isInitialized = false;

	// Create socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
		throw InvalidSocket();
	std::cout << "Socket initialized!" << std::endl;

	// Fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	if (inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr) != 1) {
		std::cerr << "Error while filling ip address into hint" << std::endl;
		return false;
	}

	std::cout << "Hint structure filled" << std::endl;

	// Connect to server
	std::cout << "Trying to connect to server" << std::endl;
	isConnected = true;
	
	int connRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connRes = SOCKET_ERROR) {
		isConnected = false;
		std::cerr << "Couln't connect to server!" << std::endl;
	}

	if (isConnected == false)
		return isInitialized; // TODO: throw excecption that client could't connect to server

	std::cout << "Connected to server" << std::endl;

	isInitialized = true;

	return isInitialized;
}

void Client::run()
{
	if (!isConnected) {
		std::cout << "Can't start client! Client isn't connected to a server!" << std::endl;
		_getwch();
		return;
	}

	if (!isInitialized) {
		std::cout << "Can't start client! Client isn't initialized!" << std::endl;
		_getwch();
		return;
	}

	char buffer[4096];
	std::string userInput;

	std::cout << "Starting client .." << std::endl;

	do {
		std::cout << "> ";
		std::getline(std::cin, userInput);

		if (userInput.size() > 0) {
			int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
			if (sendResult != SOCKET_ERROR) {
				// wait for response
				ZeroMemory(buffer, 4096);
				int bytesReceived = recv(sock, buffer, 4096, 0);
				if (bytesReceived > 0) {
					// echo response to console
					std::cout << "Server> " << std::string(buffer, 0, bytesReceived) << std::endl;
				}
			}
		}
	} while (userInput.size() > 0);
}

void Client::cleanUp()
{
	std::cout << "Cleaning client up" << std::endl;
	isCleanedUp = true;
	closesocket(sock);
}

bool Client::connectToServer()
{
	

	return isConnected;
}
