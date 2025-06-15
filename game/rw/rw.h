#pragma once

#include <cstdint>

typedef struct RsGlobalType RsGlobalType;
struct RsGlobalType
{
	const char* app_name;
	int32_t width;
	int32_t height;
	int32_t videoMode;
	int32_t maximumWidth;
	int32_t maximumHeight;
	int32_t maxFPS;
};
extern RsGlobalType* RsGlobal;
namespace rw
{
	void Initialise();
}
