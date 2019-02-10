#include "Simple_Chat.hpp"

#include <cstring>

int main(int argc, char* argv[])
{
	SimpleChat app;
	
	if (argc > 1 && (strcmp(argv[1], "--help") || strcmp(argv[1], "-h")))
		app.print_usage();

	if (argc == 1 || argc >= 1  && (strcmp(argv[1], app.modes[SimpleChat::NORMAL].c_str()) == 0))
		app.start_application(SimpleChat::NORMAL);

	return 0;
}