#include "SimpleClient.hpp"

#include <iostream>

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

	do
	{
		// Prompt the user for some text
		std::cout << "> ";
		getline(std::cin, userInput);

		if (userInput.size() > 0) {
			// Send the text
			int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
			if (sendResult != SOCKET_ERROR) {
				//Wait for response
				ZeroMemory(buf, 4096);
				int bytesReceived = recv(sock, buf, 4096, 0);

				if (bytesReceived > 0) {
					// Echo response to console
					std::cout << "SERVER> " << std::string(buf, 0, bytesReceived) << std::endl;
				}
			}
		}
	} while (userInput.size() > 0);
}
