#include "playerpool.h"

CRemotePlayer* CPlayerPool::GetAt(uint16_t id)
{
	return m_pPlayers[id];
}
