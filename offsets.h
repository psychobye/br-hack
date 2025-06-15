#pragma once

#include <vector>
#include <string>

enum eArchType
{
	ARM,
	ARM64,
	CURRENT
};

class COffset
{
public:
	static void Initialise();
	static void Add(const char* name, uintptr_t addr, eArchType arch);
	static uintptr_t Get(const char* name);
	
	struct stOffset
	{
		std::string name;
		uintptr_t addr;
		eArchType arch;
	};
private:
	static std::vector<stOffset> m_offsets;
};
