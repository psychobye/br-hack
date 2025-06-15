#include "netrpc.h"
#include "xorstr.h"

#include "plugin.h"

void DialogBoxRPC(RPCParameters* rpcParams)
{
	reinterpret_cast<void(*)(RPCParameters*)>(CGameAPI::GetBase(xorstr("RPC::DialogBox")))(rpcParams);
}

void RegisterRPCs(RakClientInterface* pInterface)
{
	// pInterface->RegisterAsRemoteProcedureCall(&RPC_ScrDialogBox, DialogBoxRPC);
}
