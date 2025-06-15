#include "offsets.h"
#include "xorstr.h"

std::vector<COffset::stOffset> COffset::m_offsets;

void COffset::Initialise()
{
#ifdef __arm__
	// 32 bit
	Add(xorstr("RwInitialised"), 0x4849729, eArchType::ARM);
	Add(xorstr("RsGlobal"), 0x4E4723C, eArchType::ARM);
	Add(xorstr("JNILib_step"), 0x3E4911, eArchType::ARM);
	Add(xorstr("TouchEvent"), 0x3E4B19, eArchType::ARM);
	Add(xorstr("CNetGame::ProcessNetwork"), 0x2EB941, eArchType::ARM);
	Add(xorstr("CNetGame::Packet_ConnectionLost"), 0x2EC701, eArchType::ARM);
	Add(xorstr("CNetGame::Packet_AimSync"), 0x2ECDDC, eArchType::ARM);
	
	Add(xorstr("CNetGame::m_pRakClient"), 0x486F30C, eArchType::ARM);
	uintptr_t ng_pRakClient = Get(xorstr("CNetGame::m_pRakClient"));
	Add(xorstr("CNetGame::m_iGameState"), ng_pRakClient + 4, eArchType::ARM);
	Add(xorstr("CNetGame::m_pPlayerPool"), ng_pRakClient + 8, eArchType::ARM);
	Add(xorstr("CNetGame::m_pVehiclePool"), ng_pRakClient + 12, eArchType::ARM);
	Add(xorstr("CNetGame::m_pPickupPool"), ng_pRakClient + 16, eArchType::ARM);
	Add(xorstr("CNetGame::m_pTextLabelPool"), ng_pRakClient + 20, eArchType::ARM);
	Add(xorstr("CNetGame::m_pTextDrawPool"), ng_pRakClient + 24, eArchType::ARM);
	Add(xorstr("CNetGame::m_pGangZonePool"), ng_pRakClient + 28, eArchType::ARM);
	Add(xorstr("CNetGame::m_pActorPool"), ng_pRakClient + 32, eArchType::ARM);
	Add(xorstr("CNetGame::m_pObjectPool"), ng_pRakClient + 36, eArchType::ARM);
	Add(xorstr("CNetGame::m_pChatBubblePool"), ng_pRakClient + 40, eArchType::ARM);
	Add(xorstr("CNetGame::m_pWayPointPool"), ng_pRakClient + 44, eArchType::ARM);
	// Add(xorstr("CNetGame::m_fNameTagsDrawDistance"), 0x4858CDC, eArchType::ARM);
	// Add(xorstr("CNetGame::m_byteWorldTime"), 0x4869F02, eArchType::ARM);
	Add(xorstr("CNetTextDrawPool::SetServerLogo"), 0x3452ED, eArchType::ARM);
	Add(xorstr("CNetVehiclePool::New"), 0x346AC1, eArchType::ARM);
	
	Add(xorstr("CRemotePlayer::StoreAimSyncData"), 0x33F015, eArchType::ARM);
	Add(xorstr("CRemotePlayer::StoreSyncData"), 0x33F0F5, eArchType::ARM);
	Add(xorstr("CRemotePlayer::StoreInCarSyncData"), 0x340691, eArchType::ARM);
	Add(xorstr("CRemotePlayer::StorePassengerSyncData"), 0x340B8D, eArchType::ARM);
	Add(xorstr("CRemotePlayer::StoreBulletSyncData"), 0x3408A5, eArchType::ARM);
	
	Add(xorstr("RakClient::RegisterAsRemoteProcedureCall"), 0x451FED, eArchType::ARM);
	Add(xorstr("CChat::AddDebugMessage"), 0x38B1B1, eArchType::ARM);
#elif __aarch64__
	// 64 bit
	Add(xorstr("CChat::AddDebugMessage"), 0x38B1B1, eArchType::ARM);
#endif
}

void COffset::Add(const char* name, uintptr_t addr, eArchType arch)
{
	stOffset nOffset;
	nOffset.name = name;
	nOffset.addr = addr;
	nOffset.arch = arch;
	m_offsets.push_back(nOffset);
}

uintptr_t COffset::Get(const char* name)
{
	uintptr_t result = 0;
	for (const auto& offset : m_offsets)
	{
		bool isArchMatch = false;

#if defined(__arm__)
		isArchMatch = (offset.arch == eArchType::ARM || offset.arch == eArchType::CURRENT);
#elif defined(__aarch64__)
		isArchMatch = (offset.arch == eArchType::ARM64 || offset.arch == eArchType::CURRENT);
#endif

		if (isArchMatch && !strcasecmp(name, offset.name.c_str()))
		{
			result = offset.addr;
			break;
		}
	}
	return result;
}