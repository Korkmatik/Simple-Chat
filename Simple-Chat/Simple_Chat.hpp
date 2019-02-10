#pragma once

#include "Main_Menu.hpp"

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

	SimpleChat::MODE mode;

	void normal_mode();

	[[ noreturn ]] void quit_application();
};

