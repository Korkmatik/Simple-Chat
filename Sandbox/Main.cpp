#include "Server.hpp"

int main() 
{
	Server s(8080);

	if (s.init())
		s.run();

	cout << "Press any key to quit" << endl;
	_getch();

	return 0;
}