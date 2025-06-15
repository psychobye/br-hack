#include "chat.h"
#include "xorstr.h"

#include "plugin.h"

void CChat::AddDebugMessage(const char* msg, ...) {
    char buffer[1024];
    va_list args;
    
    va_start(args, msg);
    vsnprintf(buffer, sizeof(buffer), msg, args);
    va_end(args);
    
    reinterpret_cast<void(*)(char*)>(CGameAPI::GetBase(xorstr("CChat::AddDebugMessage")))(buffer);
}
