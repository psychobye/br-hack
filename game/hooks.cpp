#include "hooks.h"
#include "xorstr.h"

extern bool g_bInitGameProcess;

RakClientInterface* pRakClient = RakNetworkFactory::GetRakClientInterface();

void (*orig_CNetTextDrawPool__SetServerLogo)(uintptr_t thiz, std::string url);
void hook_CNetTextDrawPool__SetServerLogo(uintptr_t thiz, std::string url)
{
	//RegisterRPCs(pRakClient);
    orig_CNetTextDrawPool__SetServerLogo(thiz, url);
}

void (*orig_CNetGame__ProcessNetwork)();
void hook_CNetGame__ProcessNetwork()
{
    // Receive zamena packets
    CNetGame::ProcessNetwork();
}

bool (*orig_RakClient__Connect)(uintptr_t thiz, const char* host, uint16_t serverPort, uint16_t clientPort, unsigned int depreciated, int threadSleepTimer);
bool hook_RakClient__Connect(uintptr_t thiz, const char* host, uint16_t serverPort, uint16_t clientPort, unsigned int depreciated, int threadSleepTimer)
{
    return pRakClient->Connect(xorstr("127.0.0.1"), 7777, 0, 0, 5);
}

void (*orig_RakClient__RegisterAsRemoteProcedureCall)(uintptr_t thiz, BRRpcIds id, void (*functionPointer)(RPCParameters* rpcParams));
void hook_RakClient__RegisterAsRemoteProcedureCall(uintptr_t thiz, BRRpcIds id, void (*functionPointer)(RPCParameters* rpcParams))
{
	int sampRpcId = ConvertBRIDToSampID(id);
	if(sampRpcId != -1) {
		pRakClient->RegisterAsRemoteProcedureCall(&sampRpcId, functionPointer);
	}
}

bool (*orig_RakClient__RPC)( uintptr_t thiz, BRRpcIds uniqueID, RakNet::BitStream *bitStream, PacketPriority priority, BRPacketReliability reliability, char orderingChannel, bool shiftTimestamp, NetworkID networkID, RakNet::BitStream *replyFromTarget );
bool hook_RakClient__RPC( uintptr_t thiz, BRRpcIds uniqueID, RakNet::BitStream *bitStream, PacketPriority priority, BRPacketReliability reliability, char orderingChannel, bool shiftTimestamp, NetworkID networkID, RakNet::BitStream *replyFromTarget )
{
	int sampRpcId = ConvertBRIDToSampID(uniqueID);
	if(sampRpcId != -1) {
		if(sampRpcId == RPC_RequestClass && g_bInitGameProcess) {
			return false;
		}
		return pRakClient->RPC(&sampRpcId, bitStream, priority, ConvertBRToSampReliability(reliability), orderingChannel, shiftTimestamp, networkID, replyFromTarget);
	} else {
		// CChat::AddDebugMessage(xorstr("Unknown RPC: %i"), uniqueID);
	}
	return false;
}

bool (*orig_RakClient__Send)( uintptr_t thiz, RakNet::BitStream* bitStream, PacketPriority priority, BRPacketReliability reliability, char orderingChannel );
bool hook_RakClient__Send( uintptr_t thiz, RakNet::BitStream* bitStream, PacketPriority priority, BRPacketReliability reliability, char orderingChannel )
{
	RakNet::BitStream bsCopy(bitStream->GetData(), bitStream->GetNumberOfBytesUsed() + 1, false);
	uint8_t pktId;
	bsCopy.Read(pktId);
	if(pktId == BR_ID_USER_INTERFACE_SYNC) {
		uint16_t guiId;
		uint32_t jsonLen;
		bsCopy.Read(guiId);
		bsCopy.Read(jsonLen);
		if(jsonLen > 0) {
			bsCopy.Read(CGUI::buffGUI, jsonLen);
			CGUI::buffGUI[jsonLen] = 0;
			static char* buffGUI;
			if(!buffGUI) { buffGUI = new char[4096]; }
			cp1251_to_utf8(buffGUI, CGUI::buffGUI);
			if(guiId == 10) {
				if(nlohmann::json::accept(buffGUI)) {
					nlohmann::json jsonObj = nlohmann::json::parse(buffGUI);
					uint8_t btn = jsonObj["r"];
					int16_t listInput = jsonObj["l"];
					std::string input = jsonObj["i"];
					uint8_t inputLen = input.length();
					RakNet::BitStream bsSend;
					bsSend.WriteBits((unsigned char *)&CNetGame::m_nLastSAMPDialogID, 16);
					bsSend.WriteBits((unsigned char *)&btn, 8);
					bsSend.WriteBits((unsigned char *)&listInput, 16);
					bsSend.WriteBits((unsigned char *)&inputLen, 8);
					bsSend.Write(input.c_str(), inputLen);
					// CChat::AddDebugMessage("Dialog ID: %i | BTN: %i | list: %i | input: %s", CNetGame::m_nLastSAMPDialogID, btn, listInput, input.c_str());
					bool result = pRakClient->RPC(&RPC_DialogResponse, &bsSend, HIGH_PRIORITY, RELIABLE_ORDERED, 0, false, UNASSIGNED_NETWORK_ID, NULL);
					if(result) {
						// CChat::AddDebugMessage("Response sended!");
					} else {
						// CChat::AddDebugMessage("Fuck.. its not sended ..");
					}
				}
			}
			// CChat::AddDebugMessage("{ffff00}Sended JSON{ffffff}(id: %i): \"%s\"", guiId, CGUI::buffGUI);
		}
	}
	if(pktId == BR_ID_AIM_SYNC) {
		uint8_t pktAimSync = ID_AIM_SYNC;
	    uint8_t aimSyncBuffer[31] = {0};
		bsCopy.ReadBits(aimSyncBuffer, 31 * 8);
		RakNet::BitStream bsSend;
	    bsSend.WriteBits(&pktAimSync, 8);
	    bsSend.WriteBits(aimSyncBuffer, 31 * 8);
	    return pRakClient->Send(&bsSend, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
	}
	if(pktId == BR_ID_BULLET_SYNC) {
		uint8_t pktBltSync = ID_BULLET_SYNC;
	    uint8_t bltSyncBuffer[40] = {0};
		bsCopy.ReadBits(bltSyncBuffer, 40 * 8);
		RakNet::BitStream bsSend;
	    bsSend.WriteBits(&pktBltSync, 8);
	    bsSend.WriteBits(bltSyncBuffer, 40 * 8);
	    return pRakClient->Send(&bsSend, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
	}
	if(pktId == BR_ID_PLAYER_SYNC) {
		uint8_t pktPlayerSync = ID_PLAYER_SYNC;
		BROnFootSyncData data;

		bsCopy.ReadBits((unsigned char *)&data.lrAnalogLeftStick, 16);
		bsCopy.ReadBits((unsigned char *)&data.udAnalogLeftStick, 16);
		bsCopy.ReadBits((unsigned char *)&data.wKeys, 16);
		bsCopy.ReadBits((unsigned char *)&data.vecPos, 96);
		bsCopy.ReadBits((unsigned char *)&data.quatw, 32);
		bsCopy.ReadBits((unsigned char *)&data.quatx, 32);
		bsCopy.ReadBits((unsigned char *)&data.quaty, 32);
		bsCopy.ReadBits((unsigned char *)&data.quatz, 32);
		bsCopy.ReadBits((unsigned char *)&data.health, 16);
		bsCopy.ReadBits((unsigned char *)&data.armour, 16);
		bsCopy.ReadBits((unsigned char *)&data.byteCurrentWeapon, 8);
		bsCopy.ReadBits((unsigned char *)&data.byteSpecialAction, 8);
		bsCopy.ReadBits((unsigned char *)&data.vecMoveSpeed, 96);
		bsCopy.ReadBits((unsigned char *)&data.vecSurfOffsets, 96);
		bsCopy.ReadBits((unsigned char *)&data.wSurfInfo, 16);
		bsCopy.ReadBits((unsigned char *)&data.dwAnimation, 32);

		RakNet::BitStream bsSend;
		bsSend.WriteBits(&pktPlayerSync, 8);
		ConvertBROnFootSyncToSampSync(&bsSend, data);
		return pRakClient->Send(&bsSend, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
	}
	if(pktId == BR_ID_VEHICLE_SYNC) {
		uint8_t pktVehicleSync = ID_VEHICLE_SYNC;
	    BRInCarSyncData data;
	    bsCopy.ReadBits((unsigned char *)&data.VehicleID, 16);
		int vehPool = *(int *)(CGameAPI::GetBase(xorstr("CNetGame::m_pVehiclePool")));
		int veh = *(int *)(vehPool + 4 * data.VehicleID);
		if(veh) {
			*(uint8_t *)(veh + 0x1C0) = 4;
			*(uint8_t *)(veh + 0x1C4) = 8;
		}
		bsCopy.ReadBits((unsigned char *)&data.lrAnalogLeftStick, 16);
		bsCopy.ReadBits((unsigned char *)&data.udAnalogLeftStick, 16);
		bsCopy.ReadBits((unsigned char *)&data.wKeys, 16);
		bsCopy.ReadBits((unsigned char *)&data.quatw, 32);
		bsCopy.ReadBits((unsigned char *)&data.quatx, 32);
		bsCopy.ReadBits((unsigned char *)&data.quaty, 32);
		bsCopy.ReadBits((unsigned char *)&data.quatz, 32);
		bsCopy.ReadBits((unsigned char *)&data.vecPos.x, 32);
		bsCopy.ReadBits((unsigned char *)&data.vecPos.y, 32);
		bsCopy.ReadBits((unsigned char *)&data.vecPos.z, 32);
		bsCopy.ReadBits((unsigned char *)&data.vecMoveSpeed.x, 32);
		bsCopy.ReadBits((unsigned char *)&data.vecMoveSpeed.y, 32);
		bsCopy.ReadBits((unsigned char *)&data.vecMoveSpeed.z, 32);
		bsCopy.ReadBits((unsigned char *)&data.fCarHealth, 32);
		bsCopy.ReadBits((unsigned char *)&data.playerHealth, 16);
		bsCopy.ReadBits((unsigned char *)&data.playerArmour, 16);
		bsCopy.ReadBits((unsigned char *)&data.byteCurrentWeapon, 8);
		bsCopy.ReadBits((unsigned char *)&data.byteSirenOn, 8);
		bsCopy.ReadBits((unsigned char *)&data.byteLandingGearState, 8);
		bsCopy.ReadBits((unsigned char *)&data.TrailerID, 16);
	    RakNet::BitStream bsSend;
	    bsSend.WriteBits(&pktVehicleSync, 8);
	    ConvertBRInCarSyncToSampSync(&bsSend, data);
	    return pRakClient->Send(&bsSend, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
	}
	if(pktId == BR_ID_PASSENGER_SYNC) {
		uint8_t pktPassengerSync = ID_PASSENGER_SYNC;
		BRPassengerSyncData data;
		bsCopy.ReadBits((unsigned char *)&data.VehicleID, 16);
		uint8_t tempByte;
		bsCopy.ReadBits((unsigned char *)&tempByte, 7);
		data.byteSeatFlags = tempByte;
		bsCopy.ReadBits((unsigned char *)&tempByte, 1);
		data.byteDriveBy = tempByte;
		bsCopy.ReadBits((unsigned char *)&data.byteCurrentWeapon, 8);
		bsCopy.ReadBits((unsigned char *)&data.playerHealth, 16);
		bsCopy.ReadBits((unsigned char *)&data.playerArmour, 16);
		bsCopy.ReadBits((unsigned char *)&data.lrAnalog, 16);
		bsCopy.ReadBits((unsigned char *)&data.udAnalog, 16);
		bsCopy.ReadBits((unsigned char *)&data.wKeys, 16);
		bsCopy.ReadBits((unsigned char *)&data.vecPos, 96);
		RakNet::BitStream bsSend;
	    bsSend.WriteBits(&pktPassengerSync, 8);
	    ConvertBRPassengerSyncToSampSync(&bsSend, data);
	    return pRakClient->Send(&bsSend, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
	}
	
	return false;
}
