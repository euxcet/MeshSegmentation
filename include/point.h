#ifndef POINT_H
#define POINT_H

#include "defs.h"

class Vector3f {
public:
    Vector3f() : x(0.0f), y(0.0f), z(0.0f) {}
    Vector3f(float x, float y, float z) : x(x), y(y), z(z) {}
    
    float operator*(const Vector3f &p) {
        return x * p.x + y * p.y + z * p.z;
    }

    float length() {
        return sqrt(x * x + y * y + z * z);
    }

    Vector3f cross(const Vector3f &p) {
        return Vector3f(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);
    }

    float x, y, z;
};

class Point3f {
public:
    Point3f() : x(0.0f), y(0.0f), z(0.0f) {}
    Point3f(float x, float y, float z) : x(x), y(y), z(z) {}

    Vector3f operator-(const Point3f &p) {
        return Vector3f(x - p.x, y - p.y, z - p.z);
    }

    Point3f operator+(const Point3f &p) {
        return Point3f(x + p.x, y + p.y, z + p.z);
    }

    Point3f operator/(float f) {
        assert(abs(f) > 1e-9);
        return Point3f(x / f, y / f, z / f);
    }

    float x, y, z;
};

class Point3i {
public:
    Point3i() : x(0), y(0), z(0) {}
    Point3i(int x, int y, int z) : x(x), y(y), z(z) {}
    int operator[](int i) {
        if (i == 0) {
            return x;
        }
        else if (i == 1) {
            return y;
        }
        return z;
    }
    int x, y, z;
};

#endif