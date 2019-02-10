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
