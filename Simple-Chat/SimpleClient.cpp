#include "SimpleClient.hpp"
#include "ServerClientExceptions.hpp"

#include <iostream>
#include <conio.h>

SimpleClient::SimpleClient(std::string& nickname, std::string ipAddress, int port)
	: ipAddress(ipAddress), port(port), nickname(nickname), isSocketInitialized(false), isWsaInitialized(false)
{
	WSADATA data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
		throw WsaStartupFail(wsResult);
	
	isWsaInitialized = true;
}

SimpleClient::~SimpleClient()
{
	if (isSocketInitialized)
		closesocket(sock);

	if (isWsaInitialized)
		WSACleanup();

	std::cout << "[*]Client shut down!\n[>]Press any key to return to menu..." << std::endl;
	_getwch();
	system("cls");
}

void SimpleClient::initialize()
{
	// Create socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
		throw InvalidSocketFail(WSAGetLastError());

	// fill in a hint struct
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);
}

void SimpleClient::run()
{
	// connect to server
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
		throw ConnectionToSeverFailed(WSAGetLastError());
	
	isSocketInitialized = true;

	// do while loop to send and receive data
	char buf[4096];
	std::string userInput;
	std::string sendData;
	
	std::cout << "[*]Client started!\n"
		"[i]Enter nothing, if you want to shut down the connection\n"
		"[i]Enter \"cls\", if you want to clear the screen" 
		<< std::endl;

	do
	{
		// Prompt the user for some text
		std::cout << nickname << "> ";
		getline(std::cin, userInput);
		
		if (userInput.compare("cls") == 0) {
			system("cls");
			continue;
		}

		sendData = nickname + "> " + userInput;

		if (userInput.size() > 0) {
			// Send the text
			size_t sendResult = send(sock, sendData.c_str(), sendData.size() + 1, 0);
			if (sendResult != SOCKET_ERROR) {
				//Wait for response
				ZeroMemory(buf, 4096);
				int bytesReceived = recv(sock, buf, 4096, 0);

				if (bytesReceived > 0) {
					// Echo response to console
					std::cout << std::string(buf, 0, bytesReceived) << std::endl;
				}
			}
		}
	} while (userInput.size() > 0);
}
