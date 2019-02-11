#include "Server.hpp"
#include "Client.hpp"

int main() 
{
	cout << "Do you want to run a (s)erver or a (c)lient?" << endl;
	char choice = _getch();

	if (choice == 'c') {
		cout << "Client is running" << endl;
		Client c(8080, "127.0.0.1");

		if (c.init())
			c.run();
	}
	else if (choice == 's') {
		cout << "Server is running" << endl;
		Server s(8080);

		if (s.init())
			s.run();

		cout << "Press any key to quit" << endl;
		_getch();
	}
	else {
		cout << "No such option!" << endl;
		_getch();
	}



	return 0;
}