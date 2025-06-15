#pragma once

#include <cstdint>

#include "common.h"

class CRemotePlayer
{
public:
	void StoreAimSyncData(uint8_t* data, uint32_t time);
	void StoreSyncData(BROnFootSyncData* data, uint32_t time);
	void StoreInCarSyncData(BRInCarSyncData* data, uint32_t time);
	void StorePassengerSyncData(uint8_t* data, uint32_t time);
	void StoreBulletSyncData(uint8_t* data, uint32_t time);
	
public:
	uint32_t m_modelIndex;
	void* m_pPlayerPed;
	uint8_t m_szName[25];
	uint16_t m_playerId;
};

