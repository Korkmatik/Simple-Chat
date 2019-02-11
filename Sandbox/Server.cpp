#include "Server.hpp"

#include <sstream>


Server::Server(u_short port)
	: BaseObject(port)
{	
	cout << "Server created" << endl;
}


Server::~Server()
{
	if (!isCleanedUp)
		cleanUp();
}

bool Server::init()
{
	cout << "Initializing Server" << endl;

	isInitialized = false;

	// Create a socket
	listening  = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
		return isInitialized; // TODO: throw error that socket is invalid

	cout << "Socket initialized" << endl;

	// Bind an ip address and a port to a socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	cout << "IP address and port binded" << endl;

	// Tell winosck the socket is for listening
	listen(listening, SOMAXCONN);
	
	FD_ZERO(&master);
	FD_SET(listening, &master);

	isInitialized = true;

	cout << "Server initialization completed" << endl;

	return isInitialized;
}

void Server::run()
{
	cout << "Starting server .." << endl;
	
	if (!isInitialized) {
		cout << "Error: Server is not initialized yet" << endl;
		return; // TODO: throw server not initialized exception
	}

	cout << "Server started" << endl;

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

	cout << "Server going down .." << endl;
}

void Server::cleanUp()
{
	cout << "Cleaning server up" << endl;
	isCleanedUp = true;
}
