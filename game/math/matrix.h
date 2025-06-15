#pragma once

#include "vector.h"

class CMatrix
{
public:
	float rx; // 0 
	float ry; // 4
	float rz; // 8
	float rw; // 12
	float fx; // 16
	float fy; // 20
	float fz; // 24
	float fw; // 28
	float ux; // 32
	float uy; // 36
	float uz; // 40
	float uw; // 44
	float px; // 48
	float py; // 52
	float pz; // 56
	float pw; // 60
	
	void* m_attachment;
	bool m_hasRwMatrix;
	
	CVector GetPosition();
	CVector GetFront();
	CVector GetRight();
	CVector GetUp();
	
};
