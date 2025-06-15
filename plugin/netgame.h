#pragma once

#include "vendor/RakNet/RakNetworkFactory.h"
#include "vendor/RakNet/RakClient.h"
#include "vendor/RakNet/NetworkTypes.h"
#include "vendor/RakNet/PacketEnumerations.h"
#include "vendor/RakNet/SAMP/SAMPRPC.h"

#include "game/chat.h"

#include "pools/playerpool.h"

#define GAMESTATE_WAIT_CONNECT	9
#define GAMESTATE_CONNECTING	13
#define GAMESTATE_AWAIT_JOIN	15
#define GAMESTATE_CONNECTED 	14
#define GAMESTATE_RESTARTING	18
#define GAMESTATE_NONE 			0
#define GAMESTATE_DISCONNECTED	4

class CNetGame
{
public:
	static uint16_t m_nLastSAMPDialogID;
public:
	static CPlayerPool* GetPlayerPool();

	static void ProcessNetwork();
	static void SetGameState(int state);
	static int GetGameState();
	
	static void Packet_AuthKey(Packet* pkt);
	static void Packet_ConnectionLost(Packet* pkt);
	static void Packet_ConnectionSucceeded(Packet* pkt);
	
	static void Packet_AimSync(Packet* pkt);
	static void Packet_PlayerSync(Packet* pkt);
	static void Packet_VehicleSync(Packet* pkt);
	static void Packet_PassengerSync(Packet* pkt);
	static void Packet_BulletSync(Packet* pkt);
	
};
