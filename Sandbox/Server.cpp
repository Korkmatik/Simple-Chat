#include "Server.hpp"

#include <sstream>
#include <iostream>
#include <string>


Server::Server(u_short port, std::string serverName)
	: BaseObject(port), serverName(serverName)
{	
	std::cout << "Server created" << std::endl;
	connectedClients = 0;
}


Server::~Server()
{
	if (!isCleanedUp)
		cleanUp();
}

bool Server::init()
{
	std::cout << "Initializing Server" << std::endl;

	isInitialized = false;

	// Create a socket
	listening  = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
		throw InvalidSocket();

	std::cout << "Socket initialized" << std::endl;

	// Bind an ip address and a port to a socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	std::cout << "IP address and port binded" << std::endl;

	// Tell winosck the socket is for listening
	listen(listening, SOMAXCONN);
	
	FD_ZERO(&master);
	FD_SET(listening, &master);

	isInitialized = true;

	std::cout << "Server initialization completed" << std::endl;

	return isInitialized;
}

void Server::run()
{
	std::cout << "Starting server .." << std::endl;
	
	if (!isInitialized)
		throw ServerNotInitialized();

	std::cout << "Server started\n" << std::endl;

	while (true)
	{
		fd_set copy = master;

		int socketCount = select(0, &copy, nullptr, nullptr, nullptr);

		for (int i = 0; i < socketCount; i++)
		{
			SOCKET sock = copy.fd_array[i];
			if (sock == listening)
			{
				// accept a new connection
				SOCKET client = accept(listening, nullptr, nullptr);

				// add the new connection to the list of connected clients
				FD_SET(client, &master);

				// send a welcome message to the connected client
				std::string welcomeMsg = "Welcome to the " + serverName + " server!\r\n";
				send(client, welcomeMsg.c_str(), welcomeMsg.size() + 1, 0);

				std::ostringstream strStream;
				strStream << "SOCKET #" << client << " connected\r\n";
				std::string strOut = strStream.str();

				for (u_int i = 0; i < master.fd_count; i++) {
					SOCKET outSock = master.fd_array[i];
					if (outSock != listening && outSock != client)
						send(outSock, strOut.c_str(), strOut.size() + 1, 0);
				}

				std::cout << strOut << "  (" << ++connectedClients << " Clients connected)" << std::endl;
			}
			else
			{
				char buf[4096];
				ZeroMemory(buf, 4096);

				// receive message
				int bytesIn = recv(sock, buf, 4096, 0);
				if (bytesIn <= 0)
				{
					std::cout << "Socket #" << sock << " disconnected\r\n" << "  (" << --connectedClients << " Clients connected)" << std::endl;

					// drop the client
					closesocket(sock);
					FD_CLR(sock, &master);
				}
				else
				{
					// Send messsage to other clients
					for (u_int i = 0; i < master.fd_count; i++)
					{
						SOCKET outSock = master.fd_array[i];
						if (outSock != listening && outSock != sock)
						{
							std::ostringstream strStream;
							strStream << "SOCKET #" << sock << ": " << buf << "\r\n";
							std::string strOut = strStream.str();

							send(outSock, strOut.c_str(), strOut.size() + 1, 0);
						}
					}
				}
			}
		}
	}

	std::cout << "Server stopped .." << std::endl;
}

void Server::cleanUp()
{
	std::cout << "Cleaning server up" << std::endl;
	isCleanedUp = true;
}
