#pragma once

#include "Main_Menu.hpp"

#include <string>
#include <memory>

class SimpleChat
{
public:
	enum MODE {
		NORMAL,
		SERVER,
		CLIENT
	};

	SimpleChat();

	void start_application(SimpleChat::MODE mode);

private:
	// Menus
	std::unique_ptr<Main_Menu> main_menu;

	SimpleChat::MODE mode;
	std::string modes[2] = { "SERVER", "CLIENT" };

	void normal_mode();

	[[ noreturn ]] void quit_application();
};

