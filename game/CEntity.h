#pragma once

#include <cstdint>
#include "CPlaceable.h"

class CRemotePlayer;

class CEntity : public CPlaceable
{
public:
	
public:
	void* m_rwObject;
	void* m_rwLods;
	uint32_t m_type : 3;
    uint32_t m_status : 5;
    uint32_t bUsesCollision : 1;
    uint32_t bCollisionProcessed : 1;
    uint32_t bIsStatic : 1;
    uint32_t bHasContacted : 1;
    uint32_t bPedPhysics : 1;
    uint32_t bIsStuck : 1;
    uint32_t bIsInSafePosition : 1;
    uint32_t bUseCollisionRecords : 1;
    uint32_t bWasPostponed : 1;
    uint32_t bExplosionProof : 1;
    uint32_t bIsVisible : 1;
    uint32_t bHasCollided : 1;
    uint32_t bRenderScorched : 1;
    uint32_t bHasBlip : 1;
    uint32_t bIsBIGBuilding : 1;
    uint32_t bStreamBIGBuilding : 1;
    uint32_t bRenderDamaged : 1;
    uint32_t bBulletProof : 1;
    uint32_t bFireProof : 1;
    uint32_t bCollisionProof : 1;
    uint32_t bMeleeProof : 1;
    uint32_t bOnlyDamagedByPlayer : 1;
    uint32_t bStreamingDontDelete : 1;
    uint32_t bRemoveFromWorld : 1;
    uint32_t bHasHitWall : 1;
    uint32_t bImBeingRendered : 1;
    uint32_t bTouchingWater : 1;
    uint32_t bIsSubway : 1;
    uint32_t bDrawLast : 1;
    uint32_t bNoBrightHeadLights : 1;
    uint32_t bDoNotRender : 1;
    uint32_t bDistanceFade : 1;
    uint32_t m_flagE1 : 1;
    uint32_t bDontCastShadowsOn : 1;
    uint32_t bOffscreen : 1;
    uint32_t bIsStaticWaitingForCollision : 1;
    uint32_t bDontStream : 1;
    uint32_t bUnderwater : 1;
    uint32_t bHasPreRenderEffects : 1;
    uint16_t m_scanCode;
    uint16_t m_randomSeed;
    uint32_t m_modelIndex;
    uint32_t unk_0;
	void* unk_1;
	int unk_2[9];
};


