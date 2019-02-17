#pragma once

#include "Main_Menu.hpp"
#include "SimpleClientMenu.hpp"
#include "SimpleServerMenu.hpp"

#include <string>
#include <memory>
#include <array>

class SimpleChat
{
public:
	enum MODE {
		NORMAL,
		SERVER,
		CLIENT
	};
	std::array<std::string, 3> modes = { "NORMAL", "SERVER", "CLIENT" };

	SimpleChat();

	void start_application(SimpleChat::MODE mode);
	[[ noreturn ]] void print_usage();

private:
	// Menus
	std::unique_ptr<Main_Menu> main_menu;
	std::unique_ptr<SimpleClientMenu> simple_client_menu;
	std::unique_ptr<SimpleServerMenu> simple_server_menu;

	SimpleChat::MODE mode;

	void normal_mode();
	void handle_user_input(const Main_Menu::MENU_ENTRIES & user_choice);

	[[ noreturn ]] void quit_application();
};

