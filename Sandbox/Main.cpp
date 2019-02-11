#include "Server.hpp"
#include "Client.hpp"

int main() 
{
	cout << "Do you want to run a (s)erver or a (c)lient?" << endl;
	char choice = _getch();

	if (choice == 'c') {
		cout << "CLIENT\n-------------------------------------------"<< endl;
		Client c(54000, "127.0.0.1");
		if (c.init())
			c.run();

		cout << "Press any key to quit" << endl;
		_getch();
	}
	else if (choice == 's') {
		cout << "SERVER\n-------------------------------------------" << endl;
		Server s(54000);

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