#pragma once

#include <iostream>

void LENIA_ASSERT(bool cond, std::string s)
{
	if (!cond)
	{
		std::cerr << "[X]" << s << "\n";
		exit(1);
	}
}

void LENIA_INFO(std::string s)
{
	std::cout << "[-]" << s << "\n";
}