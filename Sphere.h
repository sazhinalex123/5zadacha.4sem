#pragma once
#include "Object.h"
using namespace std;
class Sphere : public Object {
	double R;
public:
	Sphere(Vector3 v0, double R, Color col = Color(255, 0, 0)) {
		this->v0 = v0;
		this->R = R;
		this->col = col;
	}
	bool intersect(double A, double B, double C, double xc, double yc, double zc, double& touch, bool& tch, int&) override {
		double d1 = ((v0.x - xc) * A / B + (v0.y - yc) + (v0.z - zc) * C / B) * ((v0.x - xc) * A / B + (v0.y - yc) + (v0.z - zc) * C / B) - (A * A / (B * B) + 1 + C * C / (B * B)) * ((v0.x - xc) * (v0.x - xc) + (v0.y - yc) * (v0.y - yc) + (v0.z - zc) * (v0.z - zc) - R * R);
		if (d1 >= 0) {
			double y1 = (((v0.x - xc) * A / B + (v0.y - yc) + (v0.z - zc) * C / B) + sqrt(d1)) / (A * A / (B * B) + 1 + C * C / (B * B));
			double y2 = (((v0.x - xc) * A / B + (v0.y - yc) + (v0.z - zc) * C / B) - sqrt(d1)) / (A * A / (B * B) + 1 + C * C / (B * B));
			if (d1 == 0) {
				tch = true;
			}
			else {
				tch = false;
			}
			touch = min(y1, y2);
			return true;
		}
		touch = 0;
		tch = 0;
		return false;
	}
	Color pixelColor(double x, double y, double z, int&) override {
		Vector3 n(2 * (x - v0.x), 2 * (y - v0.y), 2 * (z - v0.z));
		n = n.normalize();
		Vector3 a(xl - x, yl - y, zl - z);
		a = a.normalize();
		Color c = col;
		double light = n * a;
		if (light < 0) {
			light = 0;
		}
		c.red = static_cast<int>(min(c.red * light + 10, 255.0));
		c.green = static_cast<int>(min(c.green * light, 255.0));
		c.blue = static_cast<int>(min(c.blue * light, 255.0));
		return c;
	}
	void setColor(Color c) override {
		col = c;
	}
	Vector3 getCenter() override {
		return v0;
	}
};