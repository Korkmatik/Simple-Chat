#include "Simple_Chat.hpp"

#include <iostream>

SimpleChat::SimpleChat()
{
	main_menu = std::make_unique<Main_Menu>();
}

void SimpleChat::start_application(SimpleChat::MODE mode)
{
	if (mode == NORMAL)
		normal_mode();
}

void SimpleChat::print_usage()
{
	std::cout <<
		"+--------------------------------------------------------------------------+\n"
		"|                        USAGE                                             |\n"
		"+--------------------------------------------------------------------------+\n"
		"|.\\Simple-Chat.exe --help  | This help screen                              |\n"
		"|.\\Simple-Chat.exe -h      |                                               |\n"
		"+--------------------------|-----------------------------------------------+\n"
		"|.\\Simple-Chat.exe         | Start this application in normal mode         |\n"
		"|.\\Simple-Chat.exe NORMAL  |   -> You get a dialog screen where you can    |\n"
		"|                          |      choose wether you want to start a server |\n"
		"|                          |      or a client                              |\n"
		"+--------------------------|-----------------------------------------------+\n"
		"|.\\Simple-Chat.exe SERVER  | Start a chat server                           |\n"
		"|.\\Simple-Chat.exe -s      |                                               |\n"
		"+--------------------------|-----------------------------------------------+\n"
		"|.\\Simple-Chat.exe CLIENT  | Start a chat client                           |\n"
		"|.\\Simple-Chat.exe -c      |                                               |\n"
		"+--------------------------------------------------------------------------+\n"
		<< std::endl;

	exit(0);
}

void SimpleChat::normal_mode()
{
	Main_Menu::MENU_ENTRIES user_choice;

	while (1) {
		user_choice = main_menu->start_menu();
		if (user_choice == Main_Menu::EXIT)
			quit_application();
	}
}

[[ noreturn ]] void SimpleChat::quit_application()
{
	std::cout << "GOODBYE!" << std::endl;

	exit(0);
}
