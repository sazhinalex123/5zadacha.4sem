#pragma once
#include "Triangle.h"

class Cube : public Object {
	vector<Triangle*> s;
public:
	Cube(Vector3 center, Vector3 v0, Vector3 v1, Vector3 v2, Vector3 v3, double a) {
		this->v0 = center;
		Vector3 point2 = v0 - v1 * a;
		Vector3 point3 = v0 - v2 * a;
		Vector3 point4 = v0 - v3 * a;
		Vector3 point5 = v0 - v1 * a - v2 * a;
		Vector3 point6 = v0 - v1 * a - v3 * a;
		Vector3 point7 = v0 - v2 * a - v3 * a;
		Vector3 point8 = v0 - v1 * a - v2 * a - v3 * a;
		s.push_back(new Triangle(v0, point2, point3));
		s.push_back(new Triangle(point3, point2, point5));

		s.push_back(new Triangle(point7, point4, point6));
		s.push_back(new Triangle(point7, point6, point8));

		s.push_back(new Triangle(point3, v0, point4));
		s.push_back(new Triangle(point3, point4, point7));

		s.push_back(new Triangle(point5, point2, point6));
		s.push_back(new Triangle(point5, point6, point8));

		s.push_back(new Triangle(point3, point7, point5));
		s.push_back(new Triangle(point7, point8, point5));

		s.push_back(new Triangle(v0, point4, point2));
		s.push_back(new Triangle(point4, point2, point6));
	}
	bool intersect(double A, double B, double C, double xc, double yc, double zc, double& touch, bool& tch, int& c) override {
		double cubeymax = DBL_MAX;
		bool found = false;
		double touch1 = 0;
		double tch1 = 0;
#pragma omp parallel for
		for (int i = 0; i < s.size(); i++) {
			if (s[i]->intersect(A, B, C, xc, yc, zc, touch, tch, c)) {
				if (touch < cubeymax) {
					c = i;
					cubeymax = touch;
					found = true;
					touch1 = touch;
					tch1 = tch;
				}
			}
		}
		touch = touch1;
		tch = tch1;
		return found;
	}
	Color pixelColor(double x, double y, double z, int& c) override {
		return s[c]->pixelColor(x, y, z, c);
	}
	void setColor(Color c) override {
		col = c;
		for (int i = 0; i < s.size(); i++) {
			s[i]->col = c;
		}
	}
	Vector3 getCenter() override {
		return v0;
	}
};