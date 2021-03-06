#include "Server.hpp"
#include "Client.hpp"

#include <conio.h>
#include <iostream>

#define SERVER_PORT 8080

int main1() 
{
	std::cout << "Do you want to run a (s)erver or a (c)lient?" << std::endl;
	char choice = _getwch();

	if (choice == 'c') {
		std::cout << "CLIENT\n-------------------------------------------"<< std::endl;
		Client c(SERVER_PORT, "127.0.0.1");
		if (c.init())
			c.run();

		std::cout << "Press any key to quit" << std::endl;
		_getwch();
	}
	else if (choice == 's') {
		std::cout << "SERVER\n-------------------------------------------" << std::endl;
		Server s(SERVER_PORT, "Simple-Chat");

		if (s.init())
			s.run();

		std::cout << "Press any key to quit" << std::endl;
		_getwch();
	}
	else {
		std::cout << "No such option!" << std::endl;
		_getwch();
	}



	return 0;
}