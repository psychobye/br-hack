#include "CPlayerPed.h"
#include "xorstr.h"

#include "plugin.h"

CMatrix* GetBoneMatrix(CPlayerPed* ped, int bone)
{
	return ((CMatrix*(*)(uintptr_t, int))CGameAPI::GetBase(xorstr("GetBoneMatrix")))(((uintptr_t)ped), bone);
}

float CPlayerPed::GetWeaponRadiusOnScreen()
{
	return ((float(*)(CPlayerPed*))CGameAPI::GetBase(xorstr("CPlayerPed::GetWeaponRadiusOnScreen")))(this);
}

void CPlayerPed::TransformToNode(CVector* vec, int node)
{
	((void(*)(CPlayerPed*, CVector*, int))CGameAPI::GetBase(xorstr("CPed::TransformToNode")))(this, vec, node);
}

uint8_t CPlayerPed::GetCurrentWeaponID()
{
	return *(uint8_t *)(((uintptr_t)this) + 24 * *(uint8_t *)(((uintptr_t)this) + 1156) + 832);
}

void* CPlayerPed::GetCurrentWeapon()
{
	return (void *)(((uintptr_t)this) + 24 * *(uint8_t *)(((uintptr_t)this) + 1156) + 832);
}

