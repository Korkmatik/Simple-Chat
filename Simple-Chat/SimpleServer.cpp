#include "SimpleServer.hpp"

#include <iostream>
#include <conio.h>

SimpleServer::SimpleServer(std::string& nickname, unsigned int port)
	: nickname(nickname), port(port)
{
	listening = INVALID_SOCKET;
	isWsaInitialized = false;
}

SimpleServer::~SimpleServer()
{
	if (listening != INVALID_SOCKET)
		closesocket(listening);

	if (clientSocket != INVALID_SOCKET)
		closesocket(clientSocket);

	if(isWsaInitialized)
		WSACleanup();

	std::cout << "[*]Server shut down\n[>]Press any key to return to menu" << std::endl;
	_getwch();
}

void SimpleServer::initialize()
{
	// Initialize winsock
	WSAData wsData;
	WORD ver = MAKEWORD(2, 2);
	int wsaOk = WSAStartup(ver, &wsData);
	if (wsaOk != 0)
		throw WsaStartupFail(wsaOk);

	isWsaInitialized = true;

	// create a socket
	listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
		throw SocketCreationFail("listening");

	// Bind the socket to an ip address and port
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(listening, (sockaddr*)&hint, sizeof(hint)) == SOCKET_ERROR)
		throw BindFail(WSAGetLastError());

	// tell winsock the socket is for listening
	listen(listening, SOMAXCONN);
}

void SimpleServer::run()
{
	std::cout << "[*]Server started\r\n[*]Waiting for client to connect ..." << std::endl;

	// wait for a connection
	sockaddr_in client;
	int clientSize = sizeof(client);

	clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
	if (clientSocket == INVALID_SOCKET)
		throw SocketCreationFail("client");

	char host[NI_MAXHOST];
	char service[NI_MAXSERV];

	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXSERV);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0) {
		std::cout << "[*]" << host << " connected on port " << service << std::endl;
	}
	else {
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		std::cout << "[*]" << host << " connected on port " << ntohs(client.sin_port) << std::endl;
	}

	// Close listening socket
	closesocket(listening);
	listening = INVALID_SOCKET;

	// while loop: accept and echo message back to client
	char buf[4096];

	while (true) {
		ZeroMemory(buf, 4096);

		// wait for client to send data
		int bytesReceived = recv(clientSocket, buf, 4096, 0);

		if (bytesReceived <= 0) {
			std::cout << "[*]Client disconnected" << std::endl;
			break;
		}

		// echo message back to client
		send(clientSocket, buf, bytesReceived + 1, 0);
	}
}