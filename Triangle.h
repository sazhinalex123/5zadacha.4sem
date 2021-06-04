#pragma once
#include "Object.h"
class Triangle : public Object {
	Vector3 v1;
	Vector3 v2;
	double Ap, Bp, Cp, Dp;
public:
	Triangle(Vector3 v0, Vector3 v1, Vector3 v2, Color col = Color(255, 0, 0)) {
		this->v0 = v0;
		this->v1 = v1;
		this->v2 = v2;
		this->col = col;
		Ap = (v1.y - v0.y) * (v2.z - v0.z) - (v1.z - v0.z) * (v2.y - v0.y);
		Bp = (v1.z - v0.z) * (v2.x - v0.x) - (v1.x - v0.x) * (v2.z - v0.z);
		Cp = (v1.x - v0.x) * (v2.y - v0.y) - (v1.y - v0.y) * (v2.x - v0.x);
		Dp = -Ap * v0.x - Bp * v0.y - Cp * v0.z;
	}
	bool intersect(double A, double B, double C, double xc, double yc, double zc, double& touch, bool& tch, int&) override {
		double nozir = (Ap * A + Bp * B + Cp * C);
		if (abs(nozir) < DBL_MIN) {
			return false;
		}
		double t = -Dp / nozir;
		double xo = A * t;
		double yo = B * t;
		double zo = C * t;
		Vector3 o(xo, yo, zo);
		Vector3 a(v0.x, v0.y, v0.z);
		Vector3 b(v1.x, v1.y, v1.z);
		Vector3 c(v2.x, v2.y, v2.z);
		Vector3 n1 = (o - a).crossProduct(b - a);
		Vector3 n2 = (o - b).crossProduct(c - b);
		Vector3 n3 = (o - c).crossProduct(a - c);
		if (n1 * n2 < 0 || n1 * n3 < 0 || n2 * n3 < 0) {
			touch = 0;
			tch = false;
			return false;
		}
		touch = yo;
		tch = false;
		return true;
	}
	Color pixelColor(double x, double y, double z, int&) override {
		Vector3 n(Ap, Bp, Cp);
		n = n.normalize();
		Vector3 a(xl - x, yl - y, zl - z);
		if (a * n < 0) {
			n = -n;
		}
		a = a.normalize();
		Color c = col;
		double light = n * a;
		if (light < 0) {
			light = 0;
		}
		c.red = static_cast<int>(min(c.red * light + 10, 255.0));
		c.green = static_cast<int>(min(c.green * light + 10, 255.0));
		c.blue = static_cast<int>(min(c.blue * light + 10, 255.0));
		return c;
	}
	void setColor(Color c) override {
		col = c;
	}
	Vector3 getCenter() override {
		Vector3 center;
		center.x = min(min(v0.x, v1.x), v2.x) + (max(max(v0.x, v1.x), v2.x) - min(min(v0.x, v1.x), v2.x)) / 2;
		center.y = min(min(v0.y, v1.y), v2.y) + (max(max(v0.y, v1.y), v2.y) - min(min(v0.y, v1.y), v2.y)) / 2;;
		center.z = min(min(v0.z, v1.z), v2.z) + (max(max(v0.z, v1.z), v2.z) - min(min(v0.z, v1.z), v2.z)) / 2;;
		return center;
	}
};
