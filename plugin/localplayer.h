#pragma once

#include <cstdint>
#include "game/CPlayerPed.h"

class CLocalPlayer
{
public:
	const uint8_t* GetLocalPlayerName() { return m_szLocalPlayerName; }
	void SetLocalPlayerID(uint16_t id) { m_LocalPlayerID = id; }
	uint16_t GetLocalPlayerID() { return m_LocalPlayerID; }
	CPlayerPed* GetPlayerPed() { return m_pPlayerPed; };
public:
	uint16_t m_LocalPlayerID;
	uint8_t m_szLocalPlayerName[25];
	CPlayerPed* m_pPlayerPed;
};

