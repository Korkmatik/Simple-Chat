#include "Server.hpp"

#include <sstream>


Server::Server(u_short port)
	: BaseObject(port)
{
	WSAData data;
	WORD version = MAKEWORD(2, 2);
	if (WSAStartup(version, &data) != 0) {
		cerr << "Cannot init winsock" << endl;
		_getch();
	}
}


Server::~Server()
{
	WSACleanup();
}

bool Server::init()
{
	// Create a socket
	listening  = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET) {
		return false;
	}

	// Bind an ip address and a port to a socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	// Tell winosck the socket is for listening
	listen(listening, SOMAXCONN);
	
	FD_ZERO(&master);
	FD_SET(listening, &master);

	return true;
}

void Server::run()
{
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
				string welcomeMsg = "Welcome to the awesome chat server!\r\n";
				send(client, welcomeMsg.c_str(), welcomeMsg.size() + 1, 0);

				// TODO: Boradcast we have a new connection
			}
			else
			{
				char buf[4096];
				ZeroMemory(buf, 4096);

				// receive message
				int bytesIn = recv(sock, buf, 4096, 0);
				if (bytesIn <= 0)
				{
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
							ostringstream ss;
							ss << "SOCKET #" << sock << ": " << buf << "\r\n";
							string strOut = ss.str();

							send(outSock, strOut.c_str(), strOut.size() + 1, 0);
						}
					}
				}
			}
		}
	}
}

void Server::cleanUp()
{
	isCleanedUp = true;
}
