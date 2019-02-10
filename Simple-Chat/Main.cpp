#include "Simple_Chat.hpp"

#include <cstring>

int main(int argc, char* argv[])
{
	SimpleChat app;
	
	if (argc > 1) {
		if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)
			app.print_usage();

		if (strcmp(argv[1], "-s") == 0 || strcmp(argv[1], app.modes[SimpleChat::SERVER].c_str()) == 0)
			app.start_application(SimpleChat::SERVER);
		
		if (strcmp(argv[1], "-c") == 0 || strcmp(argv[1], app.modes[SimpleChat::CLIENT].c_str()) == 0)
			app.start_application(SimpleChat::CLIENT);
	}

	if (argc == 1 || argc > 1  && (strcmp(argv[1], app.modes[SimpleChat::NORMAL].c_str()) == 0))
		app.start_application(SimpleChat::NORMAL);

	return 0;
}