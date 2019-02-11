#include "Client.hpp"

#include <iostream>
#include <conio.h>

Client::Client(u_short port, string ipAdress)
	: BaseObject(port), ipAddress(ipAddress), isConnected(false)
{
	cout << "Client created" << endl;
}


Client::~Client()
{
	if (!isCleanedUp)
		cleanUp();
}

bool Client::init()
{
	cout << "Initalializing client .." << endl;

	isInitialized = false;

	// Create socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
		return isInitialized; // TODO: throw error that socket could't be created
	cout << "Socket initialized!" << endl;

	// Fill in a hint structure
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	cout << "Hint structure filled" << endl;

	if (connectToServer() == false)
		return isInitialized; // TODO: throw excecption that client coul't connect to server

	cout << "Connected to server" << endl;

	isInitialized = true;

	return isInitialized;
}

void Client::run()
{
	if (!isConnected) {
		cout << "Can't start client! Client isn't connected to a server!" << endl;
		_getch();
		return;
	}

	if (!isInitialized) {
		cout << "Can't start client! Client isn't initialized!" << endl;
		_getch();
		return;
	}

	char buffer[4096];
	string userInput;

	cout << "Starting client .." << endl;

	do {
		cout << "> ";
		getline(cin, userInput);

		if (userInput.size() > 0) {
			int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
			if (sendResult != SOCKET_ERROR) {
				// wait for response
				ZeroMemory(buffer, 4096);
				int bytesReceived = recv(sock, buffer, 4096, 0);
				if (bytesReceived > 0) {
					// echo response to console
					cout << "Server> " << string(buffer, 0, bytesReceived) << endl;
				}
			}
		}
	} while (userInput.size() > 0);
}

void Client::cleanUp()
{
	cout << "Cleaning client up" << endl;
	isCleanedUp = true;
	closesocket(sock);
}

bool Client::connectToServer()
{
	isConnected = true;

	if (connect(sock, (sockaddr*)&hint, sizeof(hint)) == SOCKET_ERROR)
		isConnected = false;

	return isConnected;
}
