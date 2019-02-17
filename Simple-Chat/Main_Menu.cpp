#include "Main_Menu.hpp"

#include <iostream>
#include <iomanip>
#include <conio.h>

Main_Menu::Main_Menu()
{
}

Main_Menu::MENU_ENTRIES Main_Menu::start_menu()
{
	Main_Menu::MENU_ENTRIES user_choice;

	while (1) {
		print_menu();
		user_choice = get_user_choice();
		if (user_choice != NO_ENTRY)
			break;
		std::cout << " Sorry, no such menu entry" << std::endl;
		_getwch();
	}

	return user_choice;
}

void Main_Menu::print_menu()
{
	system("cls");

	std::cout << "      Welcome to the Simple-Chat!\n"
				 "   Choose one of the menu entries below!\n"
				 "+-------------------------------------------+\n";

	for (size_t i = 0; i < menu_entries.size(); ++i)
		std::cout << std::setw(2) << i + 1 << " - " << menu_entries[i] << "\n";
	
	std::cout << "+-------------------------------------------+\n"
			  << " [>]Your choice: ";
}

Main_Menu::MENU_ENTRIES Main_Menu::get_user_choice()
{
	Main_Menu::MENU_ENTRIES retVal;

	char user_choice = char(_getwch());
	std::cout << user_choice << std::endl;
	user_choice = user_choice - '0' - 1;

	if (user_choice < MENU_ENTRIES::START_SERVER || user_choice >= MENU_ENTRIES::NR_MENU_ENTRIES)
		retVal = MENU_ENTRIES::NO_ENTRY;
	else
		retVal = MENU_ENTRIES(user_choice);

	return retVal;
}
