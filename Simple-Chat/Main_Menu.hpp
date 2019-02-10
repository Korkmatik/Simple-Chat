#pragma once

#include <string>
#include <vector>

class Main_Menu
{
public:
	enum MENU_ENTRIES {
		START_SERVER, CONNET_TO_SERVER, EXIT, NR_MENU_ENTRIES, NO_ENTRY
	};

	explicit Main_Menu();

	Main_Menu::MENU_ENTRIES start_menu();

private:
	std::vector<std::string> menu_entries = {
		"Start Server",
		"Connect to Server",
		"Exit"
	};
	
	void print_menu();
	Main_Menu::MENU_ENTRIES get_user_choice();
};