#include "remoteplayer.h"
#include "xorstr.h"

#include "plugin.h"

#include "game/chat.h"

void CRemotePlayer::StoreAimSyncData(uint8_t* data, uint32_t time)
{
	reinterpret_cast<void(*)(CRemotePlayer*, uint8_t*, uint32_t)>(CGameAPI::GetBase(xorstr("CRemotePlayer::StoreAimSyncData")))(this, data, time);
}

void CRemotePlayer::StoreSyncData(BROnFootSyncData* data, uint32_t time)
{
	reinterpret_cast<void(*)(CRemotePlayer*, BROnFootSyncData*, uint32_t)>(CGameAPI::GetBase(xorstr("CRemotePlayer::StoreSyncData")))(this, data, time);
}

void CRemotePlayer::StoreInCarSyncData(BRInCarSyncData* data, uint32_t time)
{
	reinterpret_cast<void(*)(CRemotePlayer*, BRInCarSyncData*, uint32_t)>(CGameAPI::GetBase(xorstr("CRemotePlayer::StoreInCarSyncData")))(this, data, time);
}

void CRemotePlayer::StorePassengerSyncData(uint8_t* data, uint32_t time)
{
	reinterpret_cast<void(*)(CRemotePlayer*, uint8_t*, uint32_t)>(CGameAPI::GetBase(xorstr("CRemotePlayer::StorePassengerSyncData")))(this, data, time);
}

void CRemotePlayer::StoreBulletSyncData(uint8_t* data, uint32_t time)
{
	reinterpret_cast<void(*)(CRemotePlayer*, uint8_t*, uint32_t)>(CGameAPI::GetBase(xorstr("CRemotePlayer::StoreBulletSyncData")))(this, data, time);
}
