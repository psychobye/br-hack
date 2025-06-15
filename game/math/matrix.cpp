#include "matrix.h"

CVector CMatrix::GetPosition()
{
	return CVector(px, py, pz);
}

CVector CMatrix::GetFront()
{
	return CVector(fx, fy, fz);
}

CVector CMatrix::GetRight()
{
	return CVector(rx, ry, rz);
}

CVector CMatrix::GetUp()
{
	return CVector(ux, uy, uz);
}


