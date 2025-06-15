#pragma once

#include "CEntryInfo.h"
#include "CEntity.h"
#include "math/vector.h"

class CPhysical : public CEntity
{
public:
    float m_fGravity;
    int32_t m_audioEntityId;
    float m_phys_unused1;
    uint32_t m_nLastTimeCollided;
    CVector m_vecMoveSpeed;
    CVector m_vecTurnSpeed;
    CVector m_vecMoveFriction;
    CVector m_vecTurnFriction;
    CVector m_vecMoveSpeedAvg;
    CVector m_vecTurnSpeedAvg;
    float m_fMass;
    float m_fTurnMass;
    float m_fForceMultiplier;
    float m_fAirResistance;
    float m_fElasticity;
    float m_fBuoyancy;
    CVector m_vecCentreOfMass;
    CEntryInfoList m_entryInfoList;
    void *m_movingListNode;
    int8_t m_phys_unused2;
    uint8_t m_nStaticFrames;
    uint8_t m_nCollisionRecords;
    CEntity *m_aCollisionRecords[6];
    float m_fDistanceTravelled;
    float m_fDamageImpulse;
    CEntity *m_pDamageEntity;
    CVector m_vecDamageNormal;
    int16_t m_nDamagePieceType;
    uint8_t bIsHeavy : 1;
    uint8_t bAffectedByGravity : 1;
    uint8_t bInfiniteMass : 1;
    uint8_t m_phy_flagA08 : 1;
    uint8_t bIsInWater : 1;
    uint8_t m_phy_flagA20 : 1;
    uint8_t bHitByTrain : 1;
    uint8_t bSkipLineCol : 1;
    uint8_t bIsFrozen : 1;
    uint8_t bDontLoadCollision : 1;
    uint8_t m_bIsVehicleBeingShifted : 1;
    uint8_t bJustCheckCollision : 1;
    uint8_t bDisableMoveForce : 1;
    uint8_t m_nSurfaceTouched;
};

