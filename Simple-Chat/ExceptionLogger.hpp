#pragma once

#include <exception>
#include <iostream>
#include <Windows.h>
#include <conio.h>

struct ExceptionLogger
{
	static inline void logException(const std::exception& e)
	{
		SYSTEMTIME time;
		GetLocalTime(&time);

		std::cerr << "[-]An error occured(" << time.wDay << "/" << time.wMonth << "/" << time.wYear << " "
			<< time.wHour << ":" << time.wMinute << "): " << e.what() <<
			"\nPress a key to return to menu ..." << std::endl;

		_getch();
	}
};