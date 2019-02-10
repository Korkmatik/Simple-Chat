#pragma once

#include "Main_Menu.hpp"
#include "Client.hpp"
#include "Server.hpp"

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
	std::unique_ptr<Server> server;
	std::unique_ptr<Client> client;

	SimpleChat::MODE mode;

	void normal_mode();
	void handle_user_input(const Main_Menu::MENU_ENTRIES & user_choice);

	[[ noreturn ]] void quit_application();
};

