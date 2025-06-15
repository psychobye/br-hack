#include "rw.h"
#include "xorstr.h"

#include "plugin.h"

RsGlobalType* RsGlobal = NULL;

namespace rw
{
	void Initialise()
	{
		RsGlobal = (RsGlobalType*)(CGameAPI::GetBase(xorstr("RsGlobal")));
	}
}
