#pragma once

#include <cstdarg>

class CChat
{
public:
	static void AddDebugMessage(const char* msg, ...);
};
