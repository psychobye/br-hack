#pragma once

#include <cmath>

class CVector
{
public:
    float x;
    float y;
    float z;
public:
    CVector() { x = y = z = 0; }
    CVector(float fx, float fy, float fz) {
        x = fx; y = fy; z = fz;
    }
    CVector operator=(CVector vec) {
        x = vec.x; y = vec.y; z = vec.z;
        return CVector(x, y, z);
    }
    CVector operator+(CVector vec) const {
        return CVector(x + vec.x, y + vec.y, z + vec.z);
    }
    CVector operator+(float val) const {
        return CVector(x + val, y + val, z + val);
    }
    CVector operator-(CVector vec) const {
        return CVector(x - vec.x, y - vec.y, z - vec.z);
    }
    CVector operator-(float val) const {
        return CVector(x - val, y - val, z - val);
    }
    CVector operator*(CVector vec) const {
        return CVector(x * vec.x, y * vec.y, z * vec.z);
    }
    CVector operator*(float val) const {
        return CVector(x * val, y * val, z * val);
    }
    CVector operator/(CVector vec) const {
        return CVector(x / vec.x, y / vec.y, z / vec.z);
    }
    CVector operator/(float val) const {
        return CVector(x / val, y / val, z / val);
    }
    CVector operator+=(CVector vec) {
        x += vec.x; y += vec.y; z += vec.z;
        return CVector(x, y, z);
    }
    CVector operator+=(float val) {
        x += val; y += val; z += val;
        return CVector(x, y, z);
    }
    CVector operator-=(CVector vec) {
        x -= vec.x; y -= vec.y; z -= vec.z;
        return CVector(x, y, z);
    }
    CVector operator-=(float val) {
        x -= val; y -= val; z -= val;
        return CVector(x, y, z);
    }
    CVector operator*=(CVector vec) {
        x *= vec.x; y *= vec.y; z *= vec.z;
        return CVector(x, y, z);
    }
    CVector operator*=(float val) {
        x *= val; y *= val; z *= val;
        return CVector(x, y, z);
    }
    CVector operator/=(CVector vec) {
        x /= vec.x; y /= vec.y; z /= vec.z;
        return CVector(x, y, z);
    }
    CVector operator/=(float val) {
        x /= val; y /= val; z /= val;
        return CVector(x, y, z);
    }
    const float length() const {
        return sqrtf(x * x + y * y + z * z);
    }
};
