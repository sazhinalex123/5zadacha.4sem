#pragma once
#include <cmath>
class Vector3 {
public:
	double x, y, z;
	Vector3(double x = 0, double y = 0, double z = 0) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vector3 normalize() {
		double r = sqrt(x * x + y * y + z * z);
		return Vector3(x / r, y / r, z / r);
	}
	double operator*(const Vector3& r) {
		double touch = 0;
		touch += x * r.x + y * r.y + z * r.z;
		return touch;
	}
	Vector3 operator*(double r) {
		return { x * r,y * r,z * r };
	}
	Vector3 operator-(const Vector3& r) {
		return Vector3(x - r.x, y - r.y, z - r.z);
	}
	Vector3 operator+(const Vector3& r) {
		return Vector3(x + r.x, y + r.y, z + r.z);
	}
	double length() const {
		return sqrt(x * x + y * y + z * z);
	}
	bool operator>(const Vector3& r) {
		if (length() > r.length()) {
			return true;
		}
		return false;
	}
	Vector3 crossProduct(Vector3 b) {
		Vector3 c;
		c.x = y * b.z - z * b.y;
		c.y = z * b.x - x * b.z;
		c.z = x * b.y - y * b.x;
		return c;
	}
	Vector3 operator-() {
		return Vector3(-x, -y, -z);
	}
};