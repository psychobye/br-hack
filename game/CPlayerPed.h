#pragma once

#include "CPhysical.h"

class CPlayerPed : public CPhysical
{
public:
	float GetWeaponRadiusOnScreen();
	void TransformToNode(CVector* vec, int node);
	uint8_t GetCurrentWeaponID();
	void* GetCurrentWeapon();
};

CMatrix* GetBoneMatrix(CPlayerPed* ped, int bone);

